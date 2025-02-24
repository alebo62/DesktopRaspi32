#include "opuscodec.h"
#include <QDebug>

OpusCodec::OpusCodec() {

	encoder = opus_encoder_create(SAMPLE_RATE, CHANNELS, APPLICATION, &err);

	decoder = opus_decoder_create(SAMPLE_RATE, CHANNELS, &err);
	err = opus_encoder_init(encoder, SAMPLE_RATE, 1, APPLICATION);
	err = opus_decoder_init(decoder, SAMPLE_RATE, 1);
	err = opus_encoder_ctl(encoder, OPUS_SET_BITRATE(BITRATE));
	err = opus_decoder_ctl(decoder, OPUS_SET_BITRATE(BITRATE));

}

void OpusCodec::compress(const QByteArray& play_buf, QByteArray& play_buf_compress)
{
	play_buf_compress.clear();

	for (int var = 0; var < play_buf.length(); var += 960)
	{
		nb = opus_encode(encoder, reinterpret_cast<const opus_int16*>(play_buf.data() + var), 480, cbits, 256);
		play_buf_compress.append(nb);
		play_buf_compress.append(reinterpret_cast<char*>(cbits), nb);
	}

	play_buf_compress.append(tail, 10);
}


void OpusCodec::decompress(const QByteArray& play_buf_compress, QByteArray& play_buf_decomp)
{
	play_buf_decomp.clear();
	nb = play_buf_compress.at(0);
	size_t delta = 1;

	for (int var = 0; var < play_buf_compress.length() - 10;)
	{
		opus_decode(decoder, reinterpret_cast<const unsigned char*>(play_buf_compress.data() + delta), nb, reinterpret_cast<opus_int16*>(cbits), 960, 0);
		play_buf_decomp.append(reinterpret_cast<char*>(cbits), 960);
		delta += nb;
		nb = play_buf_compress.at(delta++);
		var = delta;
	}
}
