

#ifndef LOGGING_HEADER
#define LOGGING_HEADER		
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#ifndef STDERR
#define STDERR 1
#endif
#define LOG(error_message) (write (STDERR, error_message, strlen(error_message)))
#define CHECK_MALLOC_ERRORS switch (errno){ \
	case ENOMEM: \
		LOG("Allocator is out of memory\n"); \
		break; \
	default: \
		LOG("Allocator failed with unknown error\n"); \
		break;\
}\

#define CHECK_WRITE_ERRORS(num_bytes) if (num_bytes < 0 ){ \
LOG("ERROR writing to output file\n"); \
switch(errno) { \
case EAGAIN: \
	LOG("file is nonblocking and write would block"); \
	break; \
case EBADF: \
	LOG("output file was not opened properly");\
	break;\
case EDESTADDRREQ:\
	LOG("file descriptor is a socket for which a peer address system has not been set to connect");\
	break;\
case EDQUOT:\
	LOG("too many disk blocks have been opened");\
	break;\
case EFAULT:\
	LOG("buffer to write is not accessible");\
	break;\
case EFBIG:\
	LOG("file exceeds implementation specific maximum file size");\
	break;\
case EINTR:\
	LOG("write call was interrupted by a signal");\
	break;\
case EINVAL:\
	LOG("file descriptor is connected to an object that can not be written too");\
	break;\
case EIO:\
	LOG("low level error occured while writing"); \
	break;\
case ENOSPC:\
	LOG("insufficient space for write");\
	break;\
case EPERM:\
	LOG("write prevented by file seal");\
	break;\
case EPIPE:\
	LOG("file is a pipe that is not open for reading");\
	break;\
}\
LOG("\n");\
}\


#define CHECK_OPEN_ERRORS(file_descriptor, filename) if (file_descriptor == -1) { \
	LOG("ERROR OPENING "); \
	LOG(filename); \
	LOG(":\n"); \
	switch(errno){ \
	case EACCES:   \
		LOG("requested access to path is not allowed\n"); \
		break;\
	case EBUSY: \
		LOG("O_EXCL is specified but file is mounted\n"); \
		break;\
	case EDQUOT: \
		LOG("out of disk space or inodes\n");\
		break; \
	case EEXIST: \
		LOG("file already exists  but tried to create new file\n");\
		break;\
	case EFAULT: \
		LOG("file path is outside of memory space\n");\
		break;\
	case EINTR: \
		LOG("call interrupted by signal handler"); \
		break;\
	case EINVAL: \
		LOG("call used invalid flags"); \
		break;\
	case EISDIR: \
		LOG("attempted to inappropriately open a directory"); \
		break;\
	case ELOOP: \
		LOG("too many symbolic links in path"); \
		break;\
	case EMFILE: \
		LOG("process opened too many files");\
		break;\
	case ENAMETOOLONG:\
		LOG("path name is too long");\
		break;\
	case ENFILE: \
		LOG("system wide limit on open files reached"); \
		break;\
	case ENODEV: \
		LOG("path refers to device that does not exist"); \
		break;\
	case ENOENT: \
		LOG("path does not exist"); \
		break;\
	case ENOMEM: \
		LOG("insufficient memory");\
		break;\
	case ENOSPC: \
		LOG("no space for new file");\
		break;\
	case ENOTDIR: \
		LOG("component in path inapropriately used as a directory");\
		break;\
	case ENXIO: \
		LOG("file is of some special type without corresponeding device"); \
		break; \
	case EOPNOTSUPP: \
		LOG("temp files are not supported");\
		break;\
	case EOVERFLOW: \
		LOG("file is too big to be opened");\
		break;\
	case EPERM: \
		LOG("file is sealed or user does not own file");\
		break;\
	case EROFS: \
		LOG("file is in a read only system and write was requested");\
		break;\
	case ETXTBSY: \
		LOG("write was requested while text is busy");\
	case EWOULDBLOCK: \
		LOG("non-block is specified with incompatible lease held on file");\
		break;\
	default: \
		LOG("file could not be opened"); \
	}\
	LOG("...\n");\
	}
	





#endif
