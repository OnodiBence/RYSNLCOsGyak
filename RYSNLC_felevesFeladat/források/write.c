#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
	// Változók deklarálása
    int fd, fd2, x, y, z, flag;
	char a=' ', b, c, str[7], q, space=' ';
	
	
    // FIFO fájlok helyei
    char * teszt = "teszt.txt";
    char * eredmeny = "eredmeny.txt";
	
	

    // Nevesített csővezetékek létrehozása
    mkfifo(teszt, 0666);
	mkfifo(eredmeny, 0666);


	// Teszt FIFO megnyitása csak olvasásra
    fd = open(teszt, O_RDONLY);
    
	
	// Beolvassuk a teszt.txt-ből az adatokat
	read(fd, str, sizeof(str));
	
	
	
	// Szétszedjük a beolvasott sort,
	// és mivel ezek karakterek, átkonvertáljuk intbe őket
	a=str[0];
	x=atoi(&a);
	
	b=str[2];
	y=atoi(&b);
	
	
	c=str[4];
	z=atoi(&c);
	
	
	
	// Háromszög egyenlőtlenség ellenőrzése
	
	if(x > y && x > z)  
    {  
        flag = ((y+z) > x);  
    }
	
    else if(y > z)  
    {  
        flag = ((x+z) > y);  
    }
	
    else  
    {  
        flag = ((x+y) > z);  
    }
	
	
	// Ha 1, akkor képezhető a háromszög, ha 0 akkor nem
	
    if(flag)  
    {  
        q='1';
    }  
    else  
    {  
        q='0'; 
    }
	
	
	// A q eredményt hozzáillesztjük egy space-el az alap adatokhoz (x y z --> x y z q)
	
	strncat(str, &space, 1);
	strncat(str, &q, 1);
	
	//Lezárjuk az első (teszt) csővezetéket
	close (fd);
	
	// Megnyitjuk a másik csővezetéket, ami ugye az eredmeny.txt-re mutat
	// (Megnyitás létrehozás és írás engedéllyel, vagy csak írással ha már ott van)
	fd2 = open(eredmeny, O_CREAT | O_WRONLY);
	
	
	
	// Beírjuk a kiszámolt eredményt az eredmeny.txt-be
	write(fd2, str, strlen(str)+1);
	
	
	// Majd lezárjuk a második csővezetéket is.
	close (fd2);
	
	return 0;
}
 
