# ifndef  CUB3D_H
# define CUB3D_H

# include <math.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include "libft/libft.h"
# include <fcntl.h>

typedef struct s_data
{
	char	**map;
	char	**cub;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	*color_f;
	char	*color_c;
	int		colorf[3];
	int		colorc[3];

}				t_data;

void	add_all_cube(char **argv, t_data *map);
char	*get_next_line(int fd);
int		copy_map(t_data *map);
void	check_extension(char *str, char *ext);
void	add_path_texture(t_data *map);
void	add_color(t_data *map);
int		check_char_in_map(t_data *map);
int		check_map(t_data *map);

int		check_color(char *color);
int		add_color_in_tab_f(t_data *map);
int		add_color_in_tab_c(t_data *map);
int		check_len_int_tab(int tab[3]);
	/*	UTILS	*/
void	free_tab(char **tab);
void	free_all(t_data *map);
void	pass_space(char *str, int *i);
#endif
