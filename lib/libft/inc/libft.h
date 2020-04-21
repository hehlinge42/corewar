/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <sikpenou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 18:42:52 by sikpenou          #+#    #+#             */
/*   Updated: 2020/04/18 19:16:29 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# define EASY 0
# define ADDR 0
# define NONE 0
# define BEFORE 0
# define AFTER 1
# define LEFT 1
# define RIGHT 2
# define BOTH 3
# define FREE_CONTENT 1
# define FREE_LINKS 2
# define FREE_BOTH 3
# define KEEP_HEAD 0
# define FREE_HEAD 1
# define INITIAL_HASH_ARRAY_SIZE 4999
# define COLLISIONS_REJECTION_FACTOR 10
# define D_ARRAY_LINE_SIZE 500
# define QUIET 0
# define VERBOSE 1
# define BASE_HEX "0123456789abcdef"
# define READ_FILE_BUF 40000
# define READ_FILE_MAX_SIZE 4000000

# define MAX_ERROR 100
# define ERROR_MALLOC 1
# define ERROR_OPEN_FD 2
# define ERROR_READ 3
# define ERROR_D_ARRAY_SIZE 4
# define ERROR_MAGIC_FILE 5
# define ERROR_WITHOUT_MSG 6
# define ERROR_ERROR_TAB_FULL 7
# define ERROR_ERROR_NUMBER_IS_EXIT_SUCCESS 8
# define ERROR_ERROR_NUMBER_UNAVAILABLE 9
# define ERROR_ERROR_NUMBER_TOO_HIGH 10
# define USER_ERRORS_START 11
# define ERROR_FILE_TOO_LARGE 11

# define DEBUG 1

# include <stdarg.h>
# include <stddef.h>
# include <stdio.h>

# include "ft_errors.h"
# include "ft_lst.h"
# include "ft_printf.h"

typedef struct			s_ft_file
{
	int					fd;
	unsigned			size;
	char				*content;
}						t_file;

typedef int				(*t_func_tabmap)(void **, unsigned);

typedef struct			s_h_elem
{
	unsigned			hash;
	char				*key;
	void				*content;
}						t_h_elem;

typedef int				(*t_func_h_iter)(t_h_elem *);

typedef unsigned		(*t_func_h_hash)(char *);

typedef void			(*t_func_h_free)(void **);

typedef struct			s_h_table
{
	unsigned			size;
	unsigned			elems;
	unsigned			collisions;
	unsigned			collisions_limit;
	t_func_h_hash		hash_func;
	t_func_h_free		free_func;
	t_head				*array;
}						t_h_table;

typedef struct			s_d_array
{
	unsigned			parent_size;
	unsigned			pos;
	void				***parent_array;
}						t_d_array;

void					*easymalloc(size_t size);
void					easyfree(void **match);

unsigned long long		ft_ato_ull(const char *str, int *pos);
int						ft_abs(int a);
int						ft_atoi(const char *str);
int						ft_atoi_base(char *nbr, char *base_from);
int						ft_atoi_deref(char **str);

int						ft_check_base(char *str, char *base);
char					*ft_convert_base(char *nbr, char *base_from,
	char *base_to);

unsigned				ft_d_array_add(t_d_array *d_array, void *content);
t_d_array				*ft_d_array_alloc(void);
void					ft_d_array_free(t_d_array **d_array);
void					*ft_d_array_get_by_content(t_d_array *d_array,
	void *content);
void					*ft_d_array_get_by_index(t_d_array *d_array,
	unsigned index);

int						ft_find_next_prime(unsigned long nb);
void					ft_free(void **match);
void					ft_free_gc(void);
int						ft_free_tab(void **tab, size_t len);

t_h_table				*ft_h_new_table(void);
int						ft_h_add_elem(t_h_table *table, char *key,
	void *content);
int						ft_h_resize_array(t_h_table *table,
	unsigned new_size);
void					*ft_h_get_content(t_h_table *table, char *key);
t_h_elem				*ft_h_get_elem(t_h_table *table, char *key);
void					ft_h_free_elem(t_h_table *table, t_h_elem *hash_elem,
	int opt);
t_h_elem				*ft_h_pop_elem(t_h_table *table, char *key);
void					ft_h_free_table(t_h_table *table, int opt);
int						ft_h_iter(t_h_table *table, t_func_h_iter iter_func);

int						ft_isalnum(int c);
int						ft_isalpha(int c);
int						ft_ischarset(unsigned char c, char *charset);
int						ft_isdigit(int c);
int						ft_isspace(int c);
char					*ft_itoa(int n);
char					*ft_itoa_base(long nb, char *base_to);

unsigned				ft_lltoa_base(long long nb, char *base_to,
	char *result);

int						ft_max(int a, int b);
void					*ft_memalloc(size_t size);
int						ft_memchr_pos(const void *s, int c, size_t n);
int						ft_memcmp(const void *s1, const void *s2, size_t n);
void					*ft_memccpy(void *dst, const void *src, int c,
	size_t n);
void					*ft_memcpy(void *dst, const void *src, size_t n);
void					ft_memcset(void *o_s, int c, int stop);
void					*ft_memmove(void *dst, const void *src, size_t len);
void					*ft_memset(void *b, unsigned char c, size_t len);
int						ft_min(int a, int b);

long long int			ft_pow(long long int nb, long long int pow);
void					ft_putnbr(long long n);
void					ft_putnbr_fd(int n, int fd);

int						ft_realloc(char **zone, long curr_size_in_octs,
	long to_add_in_octs);

char					*ft_strchr(char *str, int c);
int						ft_strchr_pos(char *str, int c);
int						ft_strcmp(char *s1, char *s2);
int						ft_strcmp_heap(char *s1, char *s2);
char					*ft_strcpy(char *dest, char *src);
char					*ft_strcpy_heap(char *dest, char *src);
char					*ft_strdup(const char *s1);
char					*ft_strjoin(char *s1, char *s2);
char					*ft_strjoin_free(char **s1, char **s2, int opt);
size_t					ft_strlen(const char *s);
size_t					ft_strlen_heap(const char *s);
int						ft_strncmp(char *s1, char *s2, size_t n);
size_t					ft_strncpy(char *dst, const char *src, size_t len);
char					*ft_strrchr(const char *str, int c);
char					*ft_strrev(char *str);
char					*ft_strstr(const char *haystack, const char *needle);
char					*ft_strtrim(char const *s);
char					*ft_strsub(char const *s, unsigned int start,
	size_t len);
void					ft_swap(void **a, void **b, int opt);
void					ft_swapstr(char **a, char **b);

int						ft_tabmap(void **tab, unsigned size,
	t_func_tabmap func);

char					*ft_ulltoa(unsigned long long n);
unsigned				ft_ulltoa_base(unsigned long long n, char *base_to,
	char *result);

int						get_gc_data(int opt);
t_head					*get_gc_list(int opt);

void					h_print_elem(t_h_elem *elem);
void					h_print_index(t_h_table *table, unsigned index,
	int opt);
void					h_print_table(t_h_table *table, int opt);
void					h_print_table_data(t_h_table *table);

int						read_file(t_file *target_file, char *file_name);

#endif
