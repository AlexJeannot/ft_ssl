#include "../../incs/des.h"

void    bytes_join(t_data *current_data, char *buf, u_int64_t buf_length)
{
    char    *new_msg;

    if (!(new_msg = (char *)malloc(current_data->rc_size + buf_length)))
        fatal_error("File bytes memory allocation");
    bzero(new_msg, (current_data->rc_size + buf_length));

    memcpy(new_msg, current_data->input, current_data->rc_size);
    memcpy(&(new_msg[current_data->rc_size]), buf, buf_length);

    if (current_data->input)
        free(current_data->input);
    current_data->input = new_msg;
    current_data->rc_size += buf_length;
}

int32_t     get_file(char *file_path, u_int8_t type)
{
    int32_t fd;

    if (type == INPUT)
    {
        if ((fd = open(file_path, O_RDONLY)) == -1)
            fatal_error("file opening");
    }
    else
    {
        if ((fd = open(file_path, O_WRONLY | O_CREAT, 0644)) == -1)
            fatal_error("file opening/creation");
    }
    
    return (fd);
}

void get_file_content(t_data *current_data, int32_t fd)
{
    ssize_t     ret;
    char        buf[65535];

    bzero(&buf[0], 65535);
    while ((ret = read(fd, buf, 65534)) > 0) {
        buf[ret] = '\0';
        bytes_join(current_data, &buf[0], ret);
        bzero(&buf[0], 65535);
    }
    if (ret == -1)
        fatal_error("file reading");
}

// void get_content(t_data *data, t_args *args)
// {
//     if (args->i == FALSE)
//         get_file_content(data, args, STDIN_FILENO);
//     else
//         get_file_content(data, args, get_file(args, INPUT));
// }

// void add_output_fd(t_data *data, t_args *args)
// {
//     if (args->o == TRUE)
//         data->output_fd = get_file(args, OUTPUT);
//     else
//         data->output_fd = 1;
// }