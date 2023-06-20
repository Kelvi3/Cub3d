#ifndef INCLUDE_H
# define INCLUDE_H

# include "./minilibx-linux/mlx.h"
# include <unistd.h>
# include <fcntl.h>

typedef struct s_data {
	void	*wall;
	void	*start;
	void	*end;
	void	*item;
	void	*road;
	int		width;
	int		height;
	void	*mlx_win;
	void	*mlx;
	char	**map;
	char	**tmp_map;
	int		count_item;
	int		item_map;
	int		walk;
	char	*addr;
	void	*img;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;


#endif

