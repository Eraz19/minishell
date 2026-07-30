#ifndef GENERATOR_SERIALIZE_PRIV_H
# define GENERATOR_SERIALIZE_PRIV_H

# include "generator.h"
# include <stdbool.h>
# include <stddef.h>

bool	generator_open(int *out_h_fd, int *out_c_fd);
bool	generator_write(int fd, const char *buff);
bool	generator_write_zu(int fd, const char *opt_prefix, size_t value);
bool	serializer_report_failure(void);
bool	generator_write_header(int h_fd, const t_lr_generator *gen);
bool	generator_write_c_file(int c_fd, const t_lr_generator *gen);

#endif
