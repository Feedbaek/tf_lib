#ifndef LIBFT_H
# define LIBFT_H

# define trs(x...) { printf("[%s:%d] %s = ", __FUNC__, __LINE__, #x); printf("%s\n", x); }
# define tri(x...) { printf("[%s:%d] %s = ", __FUNC__, __LINE__, #x); printf("%d\n", x); }

int		ft_atoi(char *str);
void	ft_bzero(void *s, unsigned int n);
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_isdigit(int c);
int		ft_isprint(int c);
void	*memccpy(void *dest, const void *src, int c, unsigned int n);
int		*ft_memcmp(const void *dest, const void *src, unsigned int num);
void	*ft_memcpy(void *dest, const void *src, unsigned int n);
void	*ft_memmove(void *dest, const void *src, unsigned int n);
void	*ft_memset(void *dest, int fillchar, unsigned int len);
char	*ft_strchr(const char *str, int c);
unsigned int	ft_strlcat(char *dest, const char * src, unsigned int size);
int		ft_strlen(const char *str);
int		ft_strncmp(const char *s1, const char *s2, unsigned int n);
char	*ft_strnstr(const char *str, const char *substr, unsigned int len);
int		ft_tolower(int c);
int		ft_toupper(int c);

#endif
