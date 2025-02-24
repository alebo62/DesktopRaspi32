#ifndef OPUSCODEC_H
#define OPUSCODEC_H

#include "opus/opus.h"
#include <QByteArray>

//  apt install opus-tools libopus0 libopus-dev
class OpusCodec
{

#define FRAME_SIZE 480
#define SAMPLE_RATE 8000
#define CHANNELS 1
#define APPLICATION OPUS_APPLICATION_AUDIO
#define BITRATE 8000

	int err;
	OpusEncoder *encoder;
	OpusDecoder *decoder;

	opus_int32  nb;
	opus_uint16 temp[480];
	unsigned char cbits[1024];
	char tail[10]{0}
	;

public:
	OpusCodec();
	void compress(const QByteArray& play_buf, QByteArray& play_buf_compress);
	void decompress(const QByteArray& play_buf_decomp, QByteArray& play_buf_compress);
};

#endif // OPUSCODEC_H
