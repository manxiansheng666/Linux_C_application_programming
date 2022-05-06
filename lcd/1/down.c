#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdint.h>
#include <string.h>


#include "linux/fb.h"

int main()
{
	//打开设备
	int fd = open("/dev/fb0",O_RDWR);
	if(fd < 0)
	{
		perror("open fb device");
		exit(1);
	}

	int fd2 = open("./123.bin",O_RDONLY);

	unsigned int img[240][240];

	read(fd2,img,240*240*4);

	close(fd2);

	//获取设备的信息
	struct fb_var_screeninfo var;
	struct fb_fix_screeninfo fix;

	ioctl(fd,FBIOGET_VSCREENINFO,&var);
	ioctl(fd,FBIOGET_FSCREENINFO,&fix);

	printf("mem_base is %lx\n",fix.smem_start);
	printf("mem len is %d bytes\n",fix.smem_len);

	printf("xres is %d\n",var.xres);
	printf("yres is %d\n",var.yres);

	printf("xres_virtual is %d\n",var.xres_virtual);
	printf("yres_virtual is %d\n",var.yres_virtual);

	var.xoffset = 0;
	var.yoffset = 0;

	ioctl(fd,FBIOPAN_DISPLAY,&var);

	//进行地址映射

	uint32_t(*base)[var.xres_virtual] =  mmap(NULL, fix.smem_len,PROT_READ | PROT_WRITE , MAP_SHARED,fd, 0);

	for(int i = 0;i < 240;i++)
	{
		for(int j = 0;j < 240;j++)
			base[i][j] = img[i][j];
	}
	
	
	munmap(base,fix.smem_len);
	close(fd);
}



