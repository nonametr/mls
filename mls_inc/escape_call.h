#ifndef ESCAPE_CALL_H
#define ESCAPE_CALL_H

#define ESCAPE_GET_ENCODERS     1//data_out => Encoder[encoders_count], data_out_size => encoders_count
#define ESCAPE_GET_METRIX       2//data_out => EscapeMetrix, data_out_size => sizeof(EscapeMetrix)
#define ESCAPE_UPDATE_CHANNEL   3//data_out => EscapeUpdateChannel, data_out_size => sizeof(EscapeUpdateChannel)

//ESCAPE_GET_ENCODERS
typedef struct _EscapeEncoder
{
    char name[255];
    char image_path[255];
}EscapeEncoder, *PEscapeEncoder;

//ESCAPE_GET_METRIX
typedef struct _EscapeMetrix
{
    int height;
    int widht;
    int fps;
    int preview_scale;
}EscapeMetrix, *PEscapeMetrix;

//ESCAPE_UPDATE_CHANNEL
typedef struct _EscapeUpdateChannel
{
    char channel_name[255];
    char encoder_name[255];
    char plugin_name[255];
}EscapeUpdateChannel, *PEscapeUpdateChannel;

typedef void (*EscapeCallFunc)(int escape_call_id, void** data_out, int &data_out_size);

#endif // ESCAPE_CALL_H
