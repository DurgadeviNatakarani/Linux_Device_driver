#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<error.h>
#include<alsa/asoundlib.h>
#include<pthread.h>
#include<error.h>
#include<signal.h>
#include<fcntl.h>
#include <fdk-aac/aacenc_lib.h>
#define PCM_DEVICE "default"
#define SAMPLE_RATE 44100    
#define CHANNELS 2          
#define SAMPLE_FORMAT SND_PCM_FORMAT_S16_LE 
#define BUFFER_SIZE 4096     
#define AUDIO_DURATION 120
#define PERIOD_SIZE 1024
#define FRAME_SIZE 4 //frame_size=bits_per_sample*channels 
#define FRAME 32
short *capture_buffer;
short *write_buffer;
pthread_cond_t buffer_cond,write_complete_cond,space_available; 
pthread_mutex_t lock;


///capture thread audio data
snd_pcm_t *pcm;
HANDLE_AACENCODER encoder;
short*circular_buffer;
int write_pos = 0;
int read_pos = 0;
int data_available = 0;
int err;
int next_write=0;
void *capture_audio(void *args)
{
	while (1)
	{
		pthread_mutex_lock(&lock);
		int next = (write_pos + PERIOD_SIZE*2) % BUFFER_SIZE;
		while (next == read_pos)
			pthread_cond_wait(&space_available, &lock);
		pthread_mutex_unlock(&lock);

		err=snd_pcm_readi(pcm, circular_buffer+write_pos, PERIOD_SIZE);
		if (err < 0)
		{
			if (err == -EPIPE)
			{
				fprintf(stderr, "Overrun occurred\n");
				snd_pcm_prepare(pcm);
				continue;
			}
			else
			{
				break;
			}
		}
		printf("data read %d samples\n",err);
		pthread_mutex_lock(&lock);
		write_pos = next;
		pthread_cond_signal(&buffer_cond);
		pthread_mutex_unlock(&lock);


	}


	return NULL;
}
void *encoder_thread(void *arg) {
	int record_file = *(int *)(arg);

	short int *input_buf = (short int *)malloc(PERIOD_SIZE * 2 * sizeof(short int));
	if (!input_buf) {
		perror("malloc input_buf");
		return NULL;
	}

	uint8_t *output_buf = malloc(8192); // 2*BUFFER_SIZE
	if (!output_buf) {
		perror("malloc output_buf");
		free(input_buf);
		return NULL;
	}
	err = aacEncOpen(&encoder, 0, CHANNELS);
	if(err!=AACENC_OK)
	{
		printf("unable to open the AAC encoder\n");
		exit(0);
	}
	//AAC encoder parameters settings
	aacEncoder_SetParam(encoder, AACENC_AOT, 2);//Audio Object Type (AOT):2 = AAC-LC(by default 1024 sample frame length)
	aacEncoder_SetParam(encoder, AACENC_SAMPLERATE, SAMPLE_RATE);
	aacEncoder_SetParam(encoder, AACENC_CHANNELMODE, MODE_2);//MODE_2 = stereo
	aacEncoder_SetParam(encoder, AACENC_BITRATE, 128000);// bitrate (in bits per second).
	aacEncoder_SetParam(encoder, AACENC_TRANSMUX, 2);//ADTS(AUDIO DATA TRANSPORT STREAM)

	/*	Transport type:

		0 = RAW

		1 = LATM_MCP1

		2 = ADTS (most common)*/
	aacEncoder_SetParam(encoder, AACENC_AFTERBURNER, 1);//On (higher quality, more CPU)
	aacEncEncode(encoder, NULL, NULL, NULL, NULL);
	AACENC_InfoStruct info;
	aacEncInfo(encoder, &info);
	int frame_size = info.frameLength;

	printf("AAC frame size: %d samples\n", frame_size);
	AACENC_BufDesc in_desc = { 0 }, out_desc = { 0 };
	AACENC_InArgs in_args = { 0 };
	AACENC_OutArgs out_args = { 0 };

	// Input buffer descriptor
	int in_id = IN_AUDIO_DATA; //RAW PCM DATA
	int in_size = frame_size * CHANNELS * sizeof(short);
	int in_el_sz = sizeof(short);
	void *in_ptr = input_buf;//pointer to pcm buffer

	in_desc.numBufs = 1;//no of buffers
	in_desc.bufs = &in_ptr;
	in_desc.bufferIdentifiers = &in_id;//type of buffer
	in_desc.bufSizes = &in_size;
	in_desc.bufElSizes = &in_el_sz;
	in_args.numInSamples = frame_size * CHANNELS; //no of samples per frame

	// Output buffer descriptor
	int out_id = OUT_BITSTREAM_DATA;//encoded aac data
	int out_size = 8192;
	int out_el_sz = 1;
	void *out_ptr = output_buf;

	out_desc.numBufs = 1;
	out_desc.bufs = &out_ptr;
	out_desc.bufferIdentifiers = &out_id;
	out_desc.bufSizes = &out_size;
	out_desc.bufElSizes = &out_el_sz;



	while (1) {
		pthread_mutex_lock(&lock);

		// Wait until we have at least one frame worth of data
		while (read_pos == write_pos)   
			pthread_cond_wait(&buffer_cond, &lock);
		pthread_mutex_unlock(&lock);
		int i;
		// Copy 1024 stereo samples (2048 samples) into input buffer
		for ( i = 0; i < frame_size*2; i++) {
			input_buf[i] = circular_buffer[(read_pos + i) % BUFFER_SIZE];
			}
		printf("data copied %d \n",i--);


		AACENC_ERROR err = aacEncEncode(encoder, &in_desc, &out_desc, &in_args, &out_args);
		if (err != AACENC_OK) {
			fprintf(stderr, "Encoding error: %d\n", err);
			break;
		}

		if (out_args.numOutBytes > 0) {
			int written = write(record_file,output_buf, out_args.numOutBytes );
			if (written < 0) {
				perror("write failed");
			} else {
				printf("Encoded %d bytes\n", written);
			}
		}
			pthread_mutex_lock(&lock);
			read_pos = (read_pos + frame_size*2) % BUFFER_SIZE;
			pthread_cond_signal(&space_available);
			pthread_mutex_unlock(&lock);

		
	}

    free(input_buf);
    free(output_buf);
    return NULL;
}

void alarm_handler(int signum) {
	printf("recording completed for give time\n");
	snd_pcm_close(pcm);
	exit(0); // Terminate the program


}
void sigint_handler(int signum)
{
	printf("recording is finished\n");
	snd_pcm_close(pcm);
	exit(0);
}



int main(int argc,char **argv)
{
	if(argc<1)
	{
		printf("error message use:correct parameters\n");
		return 0;
	}
	int time=atoi(argv[1]);
	signal(SIGALRM, alarm_handler);
	signal(SIGINT,sigint_handler);
	alarm(time);
	snd_pcm_hw_params_t *param;
	int err,rate,periods;
	rate=SAMPLE_RATE;
	periods=BUFFER_SIZE/PERIOD_SIZE;
        circular_buffer = (short *)malloc(BUFFER_SIZE *4);
	if (!circular_buffer) {
		fprintf(stderr, "Error allocating memory\n");
		snd_pcm_close(pcm);
		return 1;
	}

	err=snd_pcm_open(&pcm,PCM_DEVICE,SND_PCM_STREAM_CAPTURE,0);
	if(err<0)
	{
		perror("snd_pcm_open");

		printf("error in file opening\n");
		exit(EXIT_FAILURE);

	}
	snd_pcm_nonblock(pcm, 0);
	snd_pcm_hw_params_alloca(&param);
	err=snd_pcm_hw_params_any(pcm,param);
	if(err<0)
	{
		printf("error in configuring the hardware parameters\n");
		exit(EXIT_FAILURE);
	}
	err=snd_pcm_hw_params_set_access(pcm,param,SND_PCM_ACCESS_RW_INTERLEAVED);
	if(err<0)
	{
		printf("error in setting interleaved or non-interleaved\n");
		exit(EXIT_FAILURE);
	}


	err=snd_pcm_hw_params_set_rate(pcm,param,SAMPLE_RATE,0);
	if(err<0)
	{
		printf("error in setting sample rate\n");
		exit(EXIT_FAILURE);
	}

	err=snd_pcm_hw_params_set_rate_near(pcm,param,&rate,0);
	if(err<0)
	{
		printf("error in setting near sample rate\n");
		exit(EXIT_FAILURE);
	}

	err=snd_pcm_hw_params_set_format(pcm,param,SAMPLE_FORMAT);
	if(err<0)
	{
		printf("error in setting sample format\n");
		exit(EXIT_FAILURE);
	}
	err=snd_pcm_hw_params_set_channels(pcm,param,CHANNELS);
	if(err<0)
	{
		printf("error in setting the channels\n");
		exit(EXIT_FAILURE);
	}

	err = snd_pcm_hw_params_set_buffer_size(pcm, param, BUFFER_SIZE);
	if(err<0)
	{
		printf("error in setting the buffer size\n");
		exit(EXIT_FAILURE);
	}

	err=snd_pcm_hw_params_set_period_size(pcm,param,PERIOD_SIZE,0);
	if(err<0)
	{

		printf("error in setting the perid size\n");
		perror("snd_pcm_hw_params_set_periods");
		exit(EXIT_FAILURE);
	}
	err=snd_pcm_hw_params_set_periods(pcm,param,periods,0);
	if(err<0)
	{
		perror("snd_pcm_hw_params_set_periods");
		exit(EXIT_FAILURE);
	}
	err=snd_pcm_hw_params(pcm,param);
	if(err<0)
	{
		printf("error in configuring hardware parameters\n");
		exit(EXIT_FAILURE);
	}        
	err=snd_pcm_prepare(pcm);
	if(err<0)
	{
		printf("failed to prepare a PCM  device\n");
		snd_pcm_close(pcm);
		exit(EXIT_FAILURE);
	}
	int record_file=open("output_file.aac",O_CREAT|O_RDWR|O_TRUNC,0666);
	if(record_file<0)
	{
		perror("open");
		snd_pcm_close(pcm);
	}
	pthread_t capture_thread,write_thread;
	pthread_create(&capture_thread,NULL,capture_audio,NULL);
	pthread_create(&write_thread,NULL,encoder_thread,&record_file);

	printf("audio Recording started ......Press ctrl+c to stop recording \n");

	pthread_join(capture_thread,NULL);
	pthread_join(write_thread,NULL);

	snd_pcm_close(pcm);
	close(record_file);
	return 0;
}
