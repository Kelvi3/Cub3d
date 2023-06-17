		double	posX = 2;
	double	posY = 3;
	double	dirX = -1;
	double	dirY = 0;
	int		texWidth;
	int		texHeight;

		/*double	time = 0;
		double	oldTime = 0;
		double frameTime;
		double moveSpeed;
		double rotSpeed;
		*/
		double w = 1280;
	int		xorcolor;
	int		ycolor;
	int		xycolor;
	int		x = 0;
	int		y = 0;
	double 	cameraX; // x-coordinate in camera space
	double 	rayDirX;
	double 	rayDirY;
	double 	planeX = 0;
	double 	planeY = 0.66;
	int		mapX;
	int		mapY;
	// length of ray from current position to next x or y-side
	double	sideDistX;
	double	sideDistY;
	double	deltaDistX;
	double 	deltaDistY;
	double 	perpWallDist;
	int		stepX;
	int		stepY;
	int		hit; // was there a wall hit?
	int		side;	 // was a NS or a EW wall hit?
	int 	color;
	int 	drawStart;
	int 	lineHeight;
	int		drawEnd;
	int		i;
	int		texNum;
	double	wallX;
	int		texX;
	double	step;
	double	texPos;
	int		texY;
	
	
	//while (1)
	//{
	texHeight = 64;
	texWidth = 64;
	i = 0;
	int **texture = malloc(texHeight * sizeof(int *));
	i = 0;
	
	while (i < texHeight)
	{
		texture[i] = malloc(6000 * sizeof(int));
		i++;
	}
	i = 0;
	while (i < 8)
	{
		*texture[i] = texWidth * texHeight;
		i++;
	}
	while (x < texHeight)
	{
		while (y < texHeight)
		{
			xorcolor = (x * 256 / texWidth) ^ (y * 256 / texHeight);
			ycolor = y * 256 / texHeight;
			xycolor = y * 128 / texHeight + x * 128 / texWidth;
			printf("res ======== %i\n", texWidth * y + x);
			texture[0][texWidth * y + x] = 65536 * 254 * (x != y && x != texWidth - y); // flat red texture with black cross
			texture[1][texWidth * y + x] = xycolor + 256 * xycolor + 65536 * xycolor;	 // sloped greyscale
			texture[2][texWidth * y + x] = 256 * xycolor + 65536 * xycolor;				 // sloped yellow gradient
			texture[3][texWidth * y + x] = xorcolor + 256 * xorcolor + 65536 * xorcolor; // xor greyscale
			texture[4][texWidth * y + x] = 256 * xorcolor;								 // xor green
			texture[5][texWidth * y + x] = 65536 * 192 * (x % 16 && y % 16);			 // red bricks
			texture[6][texWidth * y + x] = 65536 * ycolor;								 // red gradient
			texture[7][texWidth * y + x] = 128 + 256 * 128 + 65536 * 128;				 // flat grey texture
			y++;
		}
		x++;
	}
	i = 0;
	while (i < 50)// rendu effectue
	{
		x = 0;
		while (x < w)
		{
			cameraX = 2 * x / w - 1;
			rayDirX = dirX + planeX * cameraX;
			rayDirY = dirY + planeY * cameraX;
			mapX = (int)posX;
			mapY = (int)posY;
			deltaDistX = sqrt(1 + (double)(rayDirY * rayDirY) / (rayDirX * rayDirX));
			deltaDistY = sqrt(1 + (double)(rayDirX * rayDirX) / (rayDirY * rayDirY));
			hit = 0;
			if (rayDirX < 0)
			{
				stepX = -1;
				sideDistX = (posX - mapX) * deltaDistX;
			}
			else
			{
				stepX = 1;
				sideDistX = (mapX + 1.0 - posX) * deltaDistX;
			}
			if (rayDirY < 0)
			{
				stepY = -1;
				sideDistY = (posY - mapY) * deltaDistY;
			}
			else
			{
				stepY = 1;
				sideDistY = (mapY + 1.0 - posY) * deltaDistY;
			}
			while (hit == 0)
			{
				// jump to next map square, either in x-direction, or in y-direction
				if (sideDistX < sideDistY)
				{
					sideDistX += deltaDistX;
					mapX += stepX;
					side = 0;
				}
				else
				{
					sideDistY += deltaDistY;
					mapY += stepY;
					side = 1;
				}
				// Check if ray has hit a wall
				if (img.map[mapX][mapY] > 0)
					hit = 1;
				if (side == 0)
					perpWallDist = (sideDistX - deltaDistX);
				else
					perpWallDist = (sideDistY - deltaDistY);
				lineHeight = (int)(720 / perpWallDist);
				drawStart = -lineHeight / 2 + 720 / 2;
				if (drawStart < 0)
					drawStart = 0;
				drawEnd = lineHeight / 2 + 720 / 2;
				if (drawEnd >= 720)
					drawEnd = 720 - 1;
				texNum = img.map[mapX][mapY] - 1;
				if (side == 0)
					wallX = posY + perpWallDist * rayDirY;
				else
					wallX = posX + perpWallDist * rayDirX;
				wallX -= floor((wallX));
				texX = (int)wallX * texWidth;
				if (side == 0 && rayDirX > 0)
					texX = texWidth - texX - 1;
				if (side == 1 && rayDirY < 0)
					texX = texWidth - texX - 1;
				step = 1.0 * texHeight / lineHeight;
				texPos = (drawStart - 720 / 2 + lineHeight / 2) * step;
				y = drawStart;
				while (y < drawEnd)
				{
					texY = (int)texPos & (texHeight - 1);
					texPos += step;
					y++;
					if (side == 1)
						color = (color >> 1) & 8355711;
					mlx_pixel_put(img.mlx, img.mlx_win, x, y, color);
				}
			}
			x++;
		}
		i++;
	}
		/*while (x < w)
		{
			cameraX = 2 * x / w - 1;
			rayDirX = dirX + planeX * cameraX;
			rayDirY = dirY + planeY * cameraX;
			mapX = (int)posX;
			mapY = (int)posY;
			if (rayDirX == 0)
				deltaDistX = 1e30;
			else
				deltaDistX = 1 / rayDirX;
			if (rayDirY == 0)
				deltaDistY = 1e30;
			else
				deltaDistY = 1 / rayDirY;
			// calculate step and initial sideDist
			if (rayDirX < 0)
			{
				stepX = -1;
				sideDistX = (posX - mapX) * deltaDistX;
			}
			else
			{
				stepX = 1;
				sideDistX = (mapX + 1.0 - posX) * deltaDistX;
			}
			if (rayDirY < 0)
			{
				stepY = -1;
				sideDistY = (posY - mapY) * deltaDistY;
			}
			else
			{
				stepY = 1;
				sideDistY = (mapY + 1.0 - posY) * deltaDistY;
			}
			while (hit == 0)
			{
				// jump to next map square, either in x-direction, or in y-direction
				if (sideDistX < sideDistY)
				{
					sideDistX += deltaDistX;
					mapX += stepX;
					side = 0;
				}
				else
				{
					sideDistY += deltaDistY;
					mapY += stepY;
					side = 1;
				}
				// Check if ray has hit a wall
				if (img.map[mapX][mapY] > 0)
					hit = 1;
			}
			if (side == 0)
				perpWallDist = (sideDistX - deltaDistX);
			else
				perpWallDist = (sideDistY - deltaDistY);
			// choose wall color
			lineHeight = (int)(720 / perpWallDist);

			// calcule le pixel le plus bas et le plus haut pour remplir la bande actuelle
			lineHeight = (int)(720 / perpWallDist);

			// calculate lowest and highest pixel to fill in current stripe
			drawStart = -lineHeight / 2 + 720 / 2;
			if (drawStart < 0)
				drawStart = 0;
			drawEnd = lineHeight / 2 + 720 / 2;
			if (drawEnd >= 720)
				drawEnd = 720 - 1;
			if (img.map[mapX][mapY] == '1')
				color = 0x00FF00FF;
			else if (img.map[mapX][mapY] == '0')
				color = 0x0000FFFF;
			//else
			//color = 0x000000FF;

			// give x and y sides different brightness
			if (side == 1)
			{
				color = color / 2;
			}

			// draw the pixels of the stripe as a vertical line
			while (drawStart < drawEnd)
			{
				//printf("x = %i, draxstart = %i, drawend = %i\n", x, drawStart, drawEnd);
				mlx_pixel_put(img.mlx, img.mlx_win, drawEnd, drawStart, color);
				drawStart++;
			}
			// verLine(x, drawStart, drawEnd, color);
			x++;
		}*/
	//}
