/*

  Name:Tekfire
  Author:Edson Pérez 
  Ultima versión
  
*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <limits.h>
#include <ctype.h>  
#include <windows.h>              
#include <time.h>


#define predeftekfire "123"		//clave predefinida de tekfire
#define true 1
#define false 0          

struct mercaderia
       {
       char nombre[50];
       int stock;
       int stockIncial;
       int precio;
       }articulo[150];


struct agenda
       {
       char nombre[50];
       char direccion[50];
       char telefono[15];
       int deuda;
       }persona[100];


struct venta
       {
       char nombre[50];
       int precio;
       }lista[150];

       
struct auxiliar
       {
       char stok[CHAR_MAX];
       char precio[CHAR_MAX];
       }temp;

       
struct estadistica
       {
       char nombre[50];
       int productoVendido; 
       }ventas[150];

/* Posiciona al cursor en el lugar que queremos       */
void gotoxy(int x, int y){
	COORD coord;
	coord.X = x; coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void color(int atributo){ //Windows solo trabaja con tres colores rojo azul y verde
     
    if(atributo==1)
       SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY|FOREGROUND_RED);
	
	else if(atributo==2)
	   SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY|FOREGROUND_BLUE);
	   
    else if(atributo==3)
       SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY|FOREGROUND_GREEN);
       
     }
     
       
int horafecha()
{   

    time_t ahora;
    struct tm *fecha;
    time(&ahora);
    fecha = localtime(&ahora);
    gotoxy(63,2);
    color(2);
    printf("%d-%d-%d\n", fecha->tm_mday, fecha->tm_mon+1, fecha->tm_year+1900);
    struct tm *hora;
    time(&ahora);
    hora = localtime(&ahora);
	if(hora->tm_min<10)
		printf("%d:0%d:%d\n\t", hora->tm_hour, hora->tm_min, hora->tm_sec);
    
    else if(hora->tm_sec<10)
		printf("%d:%d:0%d\n\t", hora->tm_hour, hora->tm_min, hora->tm_sec);
    
    else if(hora->tm_hour<10)
		printf("0%d:%d:%d\n\t", hora->tm_hour, hora->tm_min, hora->tm_sec);
    
    else if(hora->tm_sec<10&&hora->tm_min<10)
		printf("%d:0%d:0%d\n\t", hora->tm_hour, hora->tm_min, hora->tm_sec);
    
    else if(hora->tm_sec<10&&hora->tm_min<10&&hora->tm_hour<10)
		printf("0%d:0%d:0%d\n\t", hora->tm_hour, hora->tm_min, hora->tm_sec);
    
    else if(hora->tm_sec<10&&hora->tm_hour<10)
		printf("0%d:%d:0%d\n\t", hora->tm_hour, hora->tm_min, hora->tm_sec);
    
    else if(hora->tm_min<10&&hora->tm_hour<10)
		printf("0%d:0%d:%d\n\t", hora->tm_hour, hora->tm_min, hora->tm_sec);
    
    else
		printf("%d:%d:%d\n\t", hora->tm_hour, hora->tm_min, hora->tm_sec);
	
	gotoxy(63,3);
    color(1);
    return(fecha->tm_mday);
    
    system("pause");
    
    }

int validadorParaNoRepetirNombre(int i)
{
     
     int x;
     int cont=0;
     
     fflush(stdin);
     for(x=0;x<i;x++)
     {
        if(0==strcmp(persona[i].nombre,persona[x].nombre));
                                                              
        else
           cont++;
                      
     }
     
     if(cont==i)
     return(0);
     
     else
     {
       printf("\n\n\tEl nombre ingresado ya esta registrado en el sistema.\n"); 
       return(1);    
     }
     
} 

int validadorParaNoRepetirArticulos(int x)
{
     
     int i;
     int cont=0;
     
     fflush(stdin);
     for(i=0;i<x;i++)
     {
        if(0==strcmp(articulo[x].nombre,articulo[i].nombre));
                                                              
        else
           cont++;
                      
     }
     
     if(cont==i)
		return(0);
     
     else
     {
       printf("\n\n\tEl articulo ingresado ya esta registrado en el sistema.\n"); 
       return(1);    
     }
     
}      
int validadorNumerico(char numero[])
{
     
     int x,y,validacionDeCarecterLista;

     fflush(stdin);  
     do{    
		gets(numero);
		y=strlen(numero);
		validacionDeCarecterLista=0;
       
		for(x=0;x<y;x++)
		{
			if(0!=isalpha(numero[x])||0!=isspace(numero[x])||numero[x]=='-')//isalpha entegra verdadero si es una letra minuscula o mayuscula
			{
				printf("\n\tArgumento solicitado incorrecto, vuelva a ingresar el dato solicitado\n\n\t");
				break;
			}
           
       
			else
				++validacionDeCarecterLista;                 
		}
       
		}while(validacionDeCarecterLista!=y);                 
                                          
     x=atoi(numero);
     return(x);
     
     
     
}       

void iniciacionFile(const FILE *pFile)
{
	
    if(pFile == NULL)
    {
		perror("Error [Al abrir archivo]");
		getchar();
		exit(EXIT_FAILURE);
    }
	                  
	else
		return;
     
}
void guardarCliente(int i)
{
     
     FILE *fp,*fp2;
     int x;
     
     fp2=fopen("NumeroFinalDeAsignacion.dat","wb+");
     fprintf(fp2,"%d",i);
     fclose(fp2);
     
     fp=fopen("clientes.dat","wb+");

     for(x=0;x<i;x++)
		fwrite(&persona[x],sizeof(persona[x]),1,fp);
     
     fclose(fp);
     fflush(fp);     
}
     
void leerClientes(int *i)
{
     FILE *fp,*fp2;
     int x;
     
     fp2=fopen("NumeroFinalDeAsignacion.dat","rb");
     fscanf(fp2,"%d",&*i);
     fclose(fp2);
               
     if(*i!=0)
     {          
       fp=fopen("clientes.dat","rb+");
       iniciacionFile(fp);
       for(x=0;x<*i;x++)
			fread(&persona[x],sizeof(persona[x]),1,fp);
       fclose(fp);
     }
               
}

void guardarArticulo(int x)
{
     
     FILE *fp,*fp2;
     int i;
     
     fp2=fopen("NumeroFinalDeAsignacionArt.dat","wb+");
     fprintf(fp2,"%d",x);
     fclose(fp2);
     
     fp=fopen("articulos.dat","wb+");
     
     for(i=0;i<x;i++)
		fwrite(&articulo[i],sizeof(articulo[i]),1,fp);
     
     fclose(fp);
     
     fflush(fp);
     
}
     
void leerContresania(int *creacionLista,char pw[])
{
     
     FILE *fp;
     fp=fopen("verificadorDeCotraseniaCreada.dat","rb");
     
     fscanf(fp,"%d",&*creacionLista);
     if(*creacionLista!=1)
     {
        fgetc(fp);                  
        fscanf(fp,"%s",pw);
     }
     
     fclose(fp);

}

void guardarContrasenia(int creacionLista,char pw[])
{
     FILE *fp;
     fp=fopen("verificadorDeCotraseniaCreada.dat","wb+");
     
     fprintf(fp,"%d",creacionLista);
     fputs(" ",fp);
     fprintf(fp,"%s",pw);
     
     fclose(fp);
     
     fflush(fp);
}
     
void leerArticulo(int *x)
{
     FILE *fp,*fp2;
     int i;
     
     fp2=fopen("NumeroFinalDeAsignacionArt.dat","rb");
     fscanf(fp2,"%d",&*x);
     fclose(fp2);
               
     if(*x!=0)
     {          
		fp=fopen("articulos.dat","rb+");
		iniciacionFile(fp);
		for(i=0;i<*x;i++)
			fread(&articulo[i],sizeof(articulo[i]),1,fp);
     
       fclose(fp);
     }
               
}

void nuevaArticulo(int x)
{
     fflush(stdin);
     
     do	{
		printf("\n\n\tIngrese el nombre del articulo:\n\t");
		gets(articulo[x].nombre);
		}
	while(validadorParaNoRepetirArticulos(x));
     
     printf("\n\tIngrese el stock:\n\t");
     articulo[x].stock=validadorNumerico(temp.stok);
     articulo[x].stockIncial=articulo[x].stock;
     printf("\n\tIngrese el precio:\n\t");
     articulo[x].precio=validadorNumerico(temp.precio);
     printf("\n\t");
     system("pause");
     system("cls()");
     
}
void borrarArticulo(int *x)
{
     int opc,ok=1,cont=0;
     int i;
     char nombre[50];
     
     fflush(stdin);
     printf("\n\n\tIngrese el nombre del articulo que desea borrar\n\t");
     gets(nombre);
     for(i=0;i<*x;i++)
     {
        if(0==strcmp(nombre,articulo[i].nombre))
        {
			printf("\n\tVa a eliminar el articulo: %s\n",nombre);
			printf("\t1.Confirmar\n");
			printf("\t2.Cancelar todo el proceso\n\t");
                                                              
           do{
           
				opc=getch();
				switch(opc)
				{
					case '1':
						for(;i<=*x;i++)
							articulo[i]=articulo[i+1];            
						printf("\n\tSe ha borrado con exito el articulo indicado\n");
						ok=0;
						*x-=1;
						printf("\n\t");
						system("pause");
						system("cls()");
						break;
                
					case '2':
						printf("\n\tSe ha anulado el proceso de borrado\n");
						ok=0;
						printf("\n\t");
						system("pause");
						system("cls()");
						break;
                
				}
                                                                   
			}while(ok);
                                                              
        }//Fin del if de comparacion
                                                              
        else
			cont++;
                      
     }//fin del for
     
                    
     if(cont==*x&&*x!=0)          //Cuando queda 1 persona y se borra el *x queda igual a 0 y por ende seria igual al contador devido a eso se coloca esta condicion
     {
        printf("\n\tNo existe el articulo buscado\n\n\t");
        system("pause");
        system("cls()");
     }  
}


void modificarArticulo(int x)
{     
     char nombre[50];
     int i,cont=0;
     int opc,ok=1;
     
     fflush(stdin);
     printf("\n\n\tIngrese el nombre del articulo el cual desea modificar:\n\t");
     gets(nombre);
     
     for(i=0;i<x;i++)
     {
		if(0==strcmp(nombre,articulo[i].nombre))
		{
			printf("\n\n\tSolo puede modificar precio y Stock\n");
			printf("\n\tSelecione la opcion:\n");
			printf("\n\t1.Modificar Precio.");
			printf("\n\t2.Modificar Stock.\n\t");
                                                              
          do{                                                                       
          opc=getch();
          
				switch(opc)
				{                                                
						case '1':
							printf("\n\n\tIngrese el nuevo precio:\n\t");
							articulo[i].precio=validadorNumerico(temp.precio);
							ok=0;
							printf("\n\t");
							system("pause");
							system("cls()");
							break;
                                                                         
						case '2':
							printf("\n\n\tIngrese el nuevo stock:\n\t");
							articulo[i].stock=validadorNumerico(temp.stok);
							ok=0;
							printf("\n\t");
							system("pause");
							system("cls()");
							break;
                                                                                     
				}		
                                                                  
			}while(ok);
                                                              
       }//Fin del If
                                                              
       else
         cont++;
                      
     }
                      
     if(cont==x)
     {
        printf("\n\tNo existe el articulo buscado\n\tPor favor escriba correctemente el nombre del articulo\n\n\t");
        system("pause");
        system("cls()");
     }
     
}
     
void consultarPrecio(int x)
{
     char nombre[50];
     int i,cont=0;
     
     fflush(stdin);
     printf("\n\n\tIngrese el nombre del articulo para ver su precio:\n\t");
     gets(nombre);
     for(i=0;i<x;i++)
     {
        if(0==strcmp(nombre,articulo[i].nombre))
        {
           printf("\n\n\tArticulo: %s\n",articulo[i].nombre);
           printf("\n\tPrecio: $%d\n",articulo[i].precio);
           printf("\n\t");
           system("pause");
           system("cls()");
        }
                      
                                                                 
        else
          cont++;
                      
        }//Fin Del For
                      
     if(cont==x)
     {
        printf("\n\tNo existe el articulo buscado\n\n\t");
        system("pause");
        system("cls()");
     }   
}

void mostrarInventario(int x)
{    
    int i;
    
    for(i=0;i<x;i++)
    {  
       color(1);
       printf("\n\t-------------------------\n");
       color(3);
       printf("\n\tNombre: %s\n",articulo[i].nombre);
       printf("\tStock: %d\n",articulo[i].stock);
       printf("\tPrecio: $%d\n",articulo[i].precio);
       color(1);
       printf("\n\t-------------------------\n");
       color(3);   
    }
                       
    printf("\n\t");
    system("pause");
    system("cls()");
    
}
    
void vender(int x,int *total, int *ok2,int *z)
{     
     char nombre[50];
     int i,cont=0;
     int opc;
     
     fflush(stdin);         
     printf("\n\n\tIngrese el nombre del articulo\n\tPara adicionarlo a lista de compras del cliente\n\t");
     gets(nombre);
     
     for(i=0;i<x;i++)
     {
        if(0==strcmp(nombre,articulo[i].nombre))
        {
			*total+=articulo[i].precio;
			articulo[i].stock-=1;
			strcpy(lista[*z].nombre,articulo[i].nombre);
			lista[*z].precio=articulo[i].precio;
			++*z;
           
			printf("\n\tDesea ingresar otro articulo\n");
			printf("\t1.Si.\n");
			printf("\t2.No.\n\t");
           
                                                              
			while(*ok2)
			{
              opc=getch(); 
              switch(opc)
              {
                 case '1':
					vender(x,total,ok2,z);//aca no va el & por ke le estaria dando la direccion de la direccion
                    break;
                                                                 
                 case '2':
					*ok2=0;
					break;
              }
                                                                                         
           }//fin del while
                                                                          
        }//fin del if
                                                              
        else
          cont++;
                      
     }//Fin del For
                      
     if(cont==x&&*z!=0)
     {
        printf("\n\tNo existe el articulo buscado\n\tPor favor escriba correctemente el nombre del articulo\n\t");
        vender(x,total,ok2,z);
     }
     
}

void ingresarDeuda(int i,int total)
{
     char nombre[50];
     int x,cont=0;
     
     fflush(stdin);
     printf("\tIngrese el nombre de la persona a la cual desea agregar la deuda\n\t");
     gets(nombre);
     for(x=0;x<i;x++)
     {
        if(0==strcmp(nombre,persona[x].nombre))
        {
			printf("\n\tHa seleccionado al cliente %s\n",persona[x].nombre);         
			printf("\tEl monto que se adicionara a su cuenta personal\n");
			persona[x].deuda+=total;
			printf("\tDeuda actual del cliente %s: $%d\n",persona[x].nombre,persona[x].deuda);
			printf("\n\t");
			system("pause");
			system("cls()");                                    
        }     
        
        else
			cont++;
                      
     }
                      
     if(cont==i)
     {
		printf("\n\tNo existe la persona buscada\n\tPor favor escriba correctemente el nombre del cliente\n\n");
		guardarCliente(i);
		system("start clientes.exe");//Para comodidad del usuario se ejecutara una ventana de apoyo con los cliente			ingresarDeuda(i,total);
     }
}
     
void modificarInventario(char nombre[],int x)
{     
     int i;
     
     for(i=0;i<x;i++)
     {
        if(0==strcmp(nombre,articulo[i].nombre))
        {                                         
			articulo[i].stock+=1;
			break;
        }                                   
     }
                      
}
     
               
void borrarArticuloLista(int *z,int *total,int x)
{
     
     char nombre[50];
     int i,cont=0;
     
     printf("\n\tEscriba el articulo que desea borrar de la lista\n\t");
     gets(nombre);
     
     for(i=0;i<*z;i++)
     {
        if(0==strcmp(nombre,lista[i].nombre))
        {
			*total-=lista[i].precio;
			modificarInventario(nombre,x);//necesito saber hasta donde llega el total de los articulos
           
			for(;i<=*z;i++)
				lista[i]=lista[i+1];
           
			--*z;
                                                                          
        }//fin del if
                                                              
        else
          cont++;
                      
     }//Fin del For
                      
     if(cont==i)
        printf("\n\tNo existe el articulo buscado\n\tPor favor escriba correctemente el nombre del articulo\n\t");        
     
     }
     
               
void finalizacionDeVenta(int x,int *total,int i,int z){
     
     FILE *archivo;
     int ok=1,ok2=1,ok3=1, td, ts, tm;
     int opc;
     int efectivo,vuelto;
     char efectivoaux[CHAR_MAX];
     int y;
     
     color(1);
     printf("\n\t-------Lista de Compra--------\n"); 
     color(3);
     
     for(y=0;y<z;y++)
        printf("\n\t%s\t\t$%d\n",lista[y].nombre,lista[y].precio);
                   
     printf("\n\tTotal $%d\n",*total);
     
     printf("\n\t1.Borrar algun articulo de la lista\n");
     printf("\n\t2.Efectuar la compra\n");
     
     do{
     opc=getch();
     
     switch(opc)
     {
     case '1':
          borrarArticuloLista(&z,total,x);
          finalizacionDeVenta(x,total,i,z);
          ok2=0;
          break;
          
     case '2':
          archivo= fopen("total.dat", "r+b");
          fscanf(archivo, "%d", &td);
          fscanf(archivo, "%d", &ts);
          fscanf(archivo, "%d", &tm);
     
          fseek(archivo, 0, SEEK_SET);
          fprintf(archivo, "%d\n", td+ (*total));
          fprintf(archivo, "%d\n", ts+ (*total));
          fprintf(archivo, "%d", tm+ (*total));
  
     
          fclose(archivo);                     
          
          printf("\n\tEl cliente va ha cancelar:\n");
          printf("\t1.Al contado.\n");
          printf("\t2.Fiado.\n\t");
     
          do{               
          opc=getch();
     
          switch (opc)
          {
              case '1':
                  do{ 
						printf("\n\tIngrese el efectivo:\n\t$");
						efectivo=validadorNumerico(efectivoaux);
                  
						if(efectivo>=*total)
						{                     
							vuelto=efectivo-*total;
							printf("\n\tVuelto del cliente $%d\n",vuelto);
							color(1);
							printf("\n\t-------Fin de la Venta--------\n");
							color(3); 
							ok=0;
							ok2=0;
							ok3=0;
							printf("\n\t");
							system("pause");
							system("cls()");
						}
                  
						else
							printf("\n\tEl efectivo ingresado debe ser mayor o igual al total de la venta\n");							
					}while(ok3);
                  
					break;
            
              case '2':
                   if(i!=0)
                   {
                       printf("\n\n\tPara ingresar el dinero seleccione el cliente\n");
                       ok=0;
                       ok2=0;
                       ingresarDeuda(i,*total);   
                   }                
                   else
                   {
                       printf("\n\tNo existe ninguna persona en la base de datos\n");
                       printf("\tA la cual asignarle la deuda\n");
                       printf("\n\tEl cliente va ha cancelar:\n");
                       printf("\t1.Al contado.\n");
                       printf("\t2.Fiado.\n\t"); 
                   }  
                   break;
              }
              
            }while(ok);             
          
          break;
     }//Fin del switch
        
     }while(ok2);
     
}       

void nueva(int i)
{     
     fflush(stdin);
     
     do{
		printf("\n\n\tIngrese el nombre de la persona:\n\t");
		gets(persona[i].nombre);
		}
	while(validadorParaNoRepetirNombre(i));
     
     printf("\n\tIngrese la direccion:\n\t");
     gets(persona[i].direccion);
     printf("\n\tIngrese el telefono:\n\t");
     gets(persona[i].telefono);
     persona[i].deuda=0;
     printf("\n\t");
     system("pause");
     system("cls()");
     
}

void mostrarLista(int i)
{    
    int x;   
    for(x=0;x<i;x++)
    { 
       color(1);
       printf("\n\t----------------------\n");
       color(3);
       printf("\n\tCliente numero %d\n",x+1);
       printf("\tNombre: %s\n",persona[x].nombre);
       printf("\tDireccion: %s\n",persona[x].direccion);
       printf("\tTelefono: %s\n",persona[x].telefono);
       printf("\tDeuda Total: $%d",persona[x].deuda);
       color(1);
       printf("\n\n\t----------------------\n");
       color(3);   
    }
    
    printf("\n\t");
    system("pause");
    system("cls()");
    
    }

void borrarPersona(int *i)
{     
     int opc,ok=1,cont=0;
     int x;
     char nombre[50];
     
     fflush(stdin);
     printf("\n\n\tIngrese el nombre de la persona que desea borrar\n\t");
     gets(nombre);
     for(x=0;x<*i;x++)
     {
        if(0==strcmp(nombre,persona[x].nombre))
        {
            printf("\n\tVa a eliminar al cliente: %s\n",nombre);
            printf("\t1.Confirmar\n");
            printf("\t2.Cancelar todo el proceso\n\t");
                                                              
            do{                                                  
				opc=getch();
            
				switch(opc)
				{          
				case '1':
                for(;x<=*i;x++)
					persona[x]=persona[x+1];
                                                
				printf("\n\tSe ha borrado con exito la persona indicada\n");
                ok=0;
                *i-=1;
                printf("\n\t");
                system("pause");
                system("cls()");
                break;

     
            case '2':
                printf("\n\tSe ha anulado el proceso de borrado\n\n\t");
                system("pause");
                system("cls()");
                ok=0;
                break;
            }
            
            }while(ok);
                                                              
        }//Fin del if de comparacion                                                            
        else
           cont++;                 
     }//fin del for
     
     if(cont==*i&&*i!=0)//Cuando queda 1 persona y se borra el *i queda igual a 0 y por ende seria igual al contador devido a eso se coloca esta condicion
     {
        printf("\tNo existe la persona buscada\n\n\t");
        system("pause");
        system("cls()");
     }
     
}

void verDeuda(int i)
{     
     char nombre[50];
     int x,cont=0;
     
     fflush(stdin);
     printf("\n\tIngrese el nombre de la persona a la cual desea ver su deuda\n\t");
     gets(nombre);
     for(x=0;x<i;x++)
     {
        if(0==strcmp(nombre,persona[x].nombre))
        {
           printf("\n\tEl cliente %s debe un total de $%d\n",nombre,persona[x].deuda);
           printf("\n\t");
           system("pause");
           system("cls()");
        }
                                                                 
        else
           cont++;
                      
     }
                      
     if(cont==i)
     {
        printf("\n\tNo existe la persona buscada\n");
        printf("\n\t");
        system("pause");
        system("cls()");
     }
                 
     }
     
void abonarDinero(int i)
{     
     char nombre[50];
     int x,cont=0;
     int monto;
     char montoaux[CHAR_MAX];
     int ok=1;
     
     fflush(stdin);
     printf("\n\n\tIngrese el nombre de la persona a la cual desea abonar dinero\n\t");
     gets(nombre);
     for(x=0;x<i;x++)
     {
        if(0==strcmp(nombre,persona[x].nombre))
        {
           if(persona[x].deuda==0)
           {
              printf("\n\tEl cliente %s no registra deudas\n\n\t",nombre);
              system("pause");
              system("cls()");
           }
                 
           else
           {
              do{
				printf("\n\n\tIngrese el monto que desea abonar\n\t$");
				monto=validadorNumerico(montoaux);
                                                              
				if(monto<=persona[x].deuda&&monto>=0)
				{
					persona[x].deuda-=monto;
					printf("\n\tAhora el cliente %s debe un total de $%d\n",nombre,persona[x].deuda);
					printf("\n\t");
					system("pause");
					system("cls()");
					ok=0;    
				}                                                                                      
				else
					printf("\n\n\tEl monto ingresado no puede ser superior a la deuda del cliente \n\tO ser un monto negaivo.");
                                                              
              }while(ok);
           }                                                   
        }    
        
        else
           cont++;
                      
     }//Fin del For
                      
     if(cont==i)
     {
         printf("\n\n\tNo existe la persona buscada\n\tPor favor escriba correctemente el nombre del cliente\n");
         printf("\n\t");
         system("pause");
         system("cls()");
     }
     
     }
     
void modificarCliente(int i)
{     
     char nombre[50];
     int x,cont=0;
     int opc,ok=1;
     
     fflush(stdin);
     printf("\n\n\tIngrese el nombre de la persona la cual desea modificar\n\t");
     gets(nombre);
     
     for(x=0;x<i;x++)
     {
         if(0==strcmp(nombre,persona[x].nombre))
         {
             printf("\n\tSolo puede modificar direccion y telefono\n");
             printf("\tSelecione la opcion:\n");
             printf("\t1.Modificar direccion.\n");
             printf("\t2.Modificar telefono.\n\t");
                                                              
             do{                                               
				opc=getch();
             
				switch(opc)
				{                                                 
             
					case '1':
						fflush(stdin);
						printf("\n\tIngrese la nueva direccion del cliente:\n\t");
						gets(persona[x].direccion);
						ok=0;
						printf("\n\t");
						system("pause");
						system("cls()");
						break;
             
                                                                         
					case '2':
						fflush(stdin);
						printf("\n\tIngrese el nuevo telefono:\n\t");
						gets(persona[x].telefono);
						ok=0;
						printf("\n\t");
						system("pause");
						system("cls()");
						break;        
                                                                           
				}
                                                                  
				}while(ok);
                                                              
         }//Fin del If
                                                              
         else
            cont++;
                      
     }//Fin del for
                      
     if(cont==i)
     {
         printf("\n\tNo existe la persona buscada\n\t\n\t");
         system("pause");
         system("cls()");
     }
     
     }
     
void verCliente(int i)
{     
     char nombre[50];
     int x,cont=0;
     
     fflush(stdin);
     printf("\n\n\tIngrese el nombre de la persona la cual desea ver su estado:\n");
     printf("\t");   
     gets(nombre);
     
     for(x=0;x<i;x++)
     {
        if(0==strcmp(nombre,persona[x].nombre))
        {
			printf("\n\tCliente Numero %d\n",x+1);
			printf("\tNombre: %s\n",persona[x].nombre);
			printf("\tDireccion: %s\n",persona[x].direccion);
			printf("\tTelefono: %s\n",persona[x].telefono);
			printf("\tDeuda Total: $%d\n",persona[x].deuda);
			printf("\n\t");
			system("pause");
			system("cls()");
        }                                                         
        else
           cont++;                
     }
                      
     if(cont==i)
     {
		printf("\n\tNo existe la persona buscada\n\tPor favor escriba correctemente el nombre del cliente\n");
        printf("\n\t");
        system("pause");
        system("cls()");
     }
                 
}

int verificadorDeContraseniaVacia(char contra)
{    
    if(contra=='\0')
    {
      printf("\n\tContrasenia vacia, vuelva a ingresar la contrasenia\n");
      return(1);
    }
    else
		return(0);
    }

//Contraseña con ECO modificado en forma cifrada    

void creacionContrasenia(char contra1[],char contra2[])
{     
     char caracter,caracter2;
     int x=0,z=0,i,y,iniciando=1,iniciando2=1;
     
     do{    
		printf("\n\tIngrese la contrasenia que desea tener como admistrador\n");
		do{
			caracter=getch();//Lee un solo carácter directamente desde el teclado, sin mostrar tal carácter en pantalla. 
     
			if(iniciando)
			{
		        printf("\t");
				iniciando=0;
			}		
     
			if(caracter!=13&&caracter!=8)
				printf("*");
     
			if(caracter==8&&x!=0)
			{
				--x;
				printf("\r\t                                                                  \r\t");//Los espacion son para borrar toda la linea
				for(i=1;i<=x;i++)
				printf("*");
			}
                           
			else
			{
				contra1[x]=caracter;
				x++;
			}
          
			}while(caracter!=13);//ascii 13 = CR ( retorno de carro )
     
		x-=1; 
		contra1[x]='\0';
     
		iniciando=1;
     
		}while(verificadorDeContraseniaVacia(contra1[0]));
      
     printf("\n\tIngrese nuevamente la contrasenia para confirmar la operacion\n");
     
     do{
                         
		do{
			caracter2=getch();//Lee un solo carácter directamente desde el teclado, sin mostrar tal carácter en pantalla. 
     
			if(iniciando2)
			{
				printf("\t");
				iniciando2=0;
			}
     
			if(caracter2!=13&&caracter2!=8)
				printf("*");
     
			if(caracter2==8&&z!=0)
			{
				--z;
				printf("\r\t                                                                  \r\t");//Los espacion son para borrar toda la linea
				for(y=1;y<=z;y++)
					printf("*");
			}
     
			else
			{
				contra2[z]=caracter2;
				z++;
			}
          
		}while(caracter2!=13);//ascii 13 = CR ( retorno de carro )
     
		z-=1; 
		contra2[z]='\0'; 
     
		iniciando2=1;
    }while(verificadorDeContraseniaVacia(contra2[0]));
     
     if(strcmp(contra1,contra2)==0)
     {
         printf("\n\tLas contrasenias se han guardado con exito\n");
         printf("\n\t");
         system("pause");
         system("cls()");
     }
     
     else
     {
         printf("\n\tLas contrasenias son diferentes,se inciara nuevamente todo el proceso\n");
         printf("\n\t");
         system("pause");
         system("cls()");
         creacionContrasenia(contra1,contra2);
     }
          
     }
     
int inciarSeccion(char pw[])
{    
     char caracter,contra[50];
     int w=0,y,iniciando=1;
     
     printf("\n\tPara iniciar seccion ingrese la contrasenia de administrador\n");
     
     do{
		caracter=getch();//Lee un solo carácter directamente desde el teclado, sin mostrar tal carácter en pantalla. 
     
     if(iniciando)
     {
        printf("\t");
        iniciando=0;
     }
     
     if(caracter!=13&&caracter!=8)
        printf("*");
     
     if(caracter==8&&w!=0)
     {
        --w;
        printf("\r\t                                                                  \r\t");//Los espacion son para borrar toda la linea
		for(y=1;y<=w;y++)
			printf("*");
     }                       
     else
     {
        contra[w]=caracter;
        w++;
     }      
     }while(caracter!=13);//ascii 13 = CR ( retorno de carro )
     
     w-=1; 
     contra[w]='\0'; 
     if(strcmp(pw,contra)==0)
     {
			printf("\n\tA ingresado al sistema correctamente\n");
			printf("\n\t");
			system("pause");
			system("cls()");
			return(1);
     } 
     else
     {
			printf("\n\tContraseña incorrecta\n");
			printf("\n\t");
			system("pause");
			system("cls()");
			return(0);    
     }     
     
}       
int iniciarTekfire(char pwtekfire[])
{
     char caracterT,contraTekfire[50];
     int w=0,y,iniciando=1;
     
     do
       {
            printf("\n\tPara iniciar seccion ingrese la contrasenia Tekfire\n");
      
            do
              {
                     caracterT=getch();//Lee un solo carácter directamente desde el teclado, sin mostrar tal carácter en pantalla. 
     
                     if(iniciando)
                     {
                             printf("\t");
                             iniciando=0;
                     }
     
                     if(caracterT!=13&&caracterT!=8)
                             printf("*");
     
                     if(caracterT==8&&w!=0)
                     {
                             --w;
                             printf("\r\t                                                                  \r\t");//Los espacion son para borrar toda la linea
                             
                             for(y=1;y<=w;y++)
                                  printf("*");
                     }
                           
                     else
                     {
                             contraTekfire[w]=caracterT;
                             w++;
                     }
          
               }
               while(caracterT!=13);//ascii 13 = CR ( retorno de carro ENTER)
     
     }
     while(!strcmp(pwtekfire,predeftekfire)); //ORIGINAL (pwtekfire,predeftekfire
     
     w-=1; 
     contraTekfire[w]='\0'; 
     
     if(strcmp(contraTekfire,predeftekfire)==0)  //ORIGINAL  (pwtekfire,contraTekfire)==0
     {
           printf("\n\tA ingresado al sistema correctamente\n");
           printf("\n\t");
           system("pause");
           system("cls()");
           return(1);
     }
     
     else
     {
           printf("\n\tContrasenia incorrecta\n");
           printf("\n\t");
           system("pause");
           system("cls()");
           return(0);
     }     
     
} 

void startzero(int *i,int *x)
{
     *i=0;
     *x=0;
     FILE *a1;
     
     a1=fopen("total.dat","w+b");
     iniciacionFile(a1);
     fprintf(a1,"0\n");
     fprintf(a1,"0\n");
     fprintf(a1,"0\n");
     fclose(a1);
     
     printf("\n\tLa restauracion del sistema se ha realizado con exito\n");
     printf("\tA continuacion el sistema se reiniciara\n\n\t");
     system("pause");
     system("cls");    
}


void burbujaMasVendidos(int x)
{   
     int i,j;
     int temp;
     char tempNombre[50];
     
     for(i=0;i<x;i++)
     {
		ventas[i].productoVendido=articulo[i].stockIncial-articulo[i].stock;
		strcpy(ventas[i].nombre,articulo[i].nombre);
     }
     
     for(i=0; i<(x-1); i++) 
     {
        for (j=i+1;j<x;j++) 
        {
           if(ventas[j].productoVendido>ventas[i].productoVendido)
           {
              temp=ventas[j].productoVendido;
              strcpy(tempNombre,ventas[j].nombre);
              ventas[j].productoVendido=ventas[i].productoVendido;
              strcpy(ventas[j].nombre,ventas[i].nombre);
              ventas[i].productoVendido=temp;
              strcpy(ventas[i].nombre,tempNombre);
           }
        }
     }
     color(1);
     printf("\n\tProductos mas vendidos.\n");
     color(3);
     
     printf("\n\tNombre\t\t\tCantidad\n\n");
     
     for(i=0;i<x;i++)
     {
       printf("\t%d.%s",i+1,ventas[i].nombre);
       gotoxy(33,i+4);
       printf("%2d\n",ventas[i].productoVendido);
     }
     
     printf("\n\t");
     system("pause");
     system("cls()");
     }

void burbujaMenosVendidos(int x){
       
     int i,j;
     int temp;
     char tempNombre[50];
     
     for(i=0;i<x;i++)
     {
       ventas[i].productoVendido=articulo[i].stockIncial-articulo[i].stock;
       strcpy(ventas[i].nombre,articulo[i].nombre);
     }
     
     for(i=0; i<(x-1); i++) 
     {
        for (j=i+1;j<x;j++) 
        {
           if(ventas[j].productoVendido<ventas[i].productoVendido)
           {
              temp=ventas[j].productoVendido;
              strcpy(tempNombre,ventas[j].nombre);
              ventas[j].productoVendido=ventas[i].productoVendido;
              strcpy(ventas[j].nombre,ventas[i].nombre);
              ventas[i].productoVendido=temp;
              strcpy(ventas[i].nombre,tempNombre);
           }
        }
     }
     color(1);
     printf("\n\tProductos menos vendidos.\n");
     color(3);
     
     printf("\n\tNombre\t\t\tCantidad\n\n");
     
     for(i=0;i<x;i++)
     {
       printf("\t%d.%s",i+1,ventas[i].nombre);
       gotoxy(33,i+4);
       printf("%2d\n",ventas[i].productoVendido);
     }
     
     printf("\n\t");
     system("pause");
     system("cls()");
     }
     

void estadisticas (int x){
     
    int td, ts, tm, d, cont=1; //contador para ir aumanetando los dias
    char opc;
    int ok=1;
     
    FILE *a1, *a2;
    a1=fopen("total.dat","r+b");
    iniciacionFile(a1);
     
    a2=fopen("fecha.dat", "r+b");
    iniciacionFile(a2);
    
    do{
                          
    color(1);
    horafecha();
    gotoxy(8,2);
    printf("Menu de estadisticas.\n");
    color(3);
    
    printf("\n\n\t\t(1)Ventas diaras,semanales y mesuales.\n");
    printf("\t\t(2)Productos mas vendidos.\n");
    printf("\t\t(3)Productos menos vendidos.\n");
    printf("\t\t(4)Retornar.\n");
    printf("\n\t\tSeleccion: ");
                        

        opc=getch();
        
        system("cls");                   

        switch(opc)
           {
                   case '1':
                         fscanf(a2,"%d", &d);
                             
                               
                         if (((horafecha()>d))||(((d==30)||(d==31))&&(horafecha()<d)))
                                  {   
                                      
                                      fscanf(a1, "%d", &td);
                                      fscanf(a1, "%d", &ts);
                                      fscanf(a1, "%d", &tm);
                                      td=0;
                                      fseek(a1, 0, SEEK_SET);
                                      fprintf(a1, "%d\n", td);
                                      fprintf(a1, "%d\n", ts);
                                      fprintf(a1, "%d\n", tm);
                                      rewind(a2);
                                      fprintf(a2, "%d", horafecha());
                                      cont++;     
                                  }         
                         if(cont%7==0)
                         {
                                      fscanf(a1, "%d", &td);
                                      fscanf(a1, "%d", &ts);
                                      fscanf(a1, "%d", &tm);
                                      ts=0;
                                      fseek(a1, 0, SEEK_SET);
                                      fprintf(a1, "%d\n", td);
                                      fprintf(a1, "%d\n", ts);
                                      fprintf(a1, "%d\n", tm);
                                      rewind(a2);
                                      fprintf(a2, "%d", horafecha());
                                      cont++;
                                      }
                       if (((d==30)||(d==31))&&(horafecha()<d))
                        {
                                      fscanf(a1, "%d", &td);
                                      fscanf(a1, "%d", &ts);
                                      fscanf(a1, "%d", &tm);
                                      tm=0;
                                      fseek(a1, 0, SEEK_SET);
                                      fprintf(a1, "%d\n", td);
                                      fprintf(a1, "%d\n", ts);
                                      fprintf(a1, "%d\n", tm);
                                      rewind(a2);
                                      fprintf(a2, "%d", horafecha());
                                      
                                      }
                               
                               fseek(a1, 0, SEEK_SET);
                               fscanf(a1, "%d", &td);
                               fscanf(a1, "%d", &ts);
                               fscanf(a1, "%d", &tm);
                               
                               
                               
                               color(1);
                               gotoxy(8,2);
                               printf("Ventas.\n");
                               color(3);
                               printf("\n\n\t\tTotal vendido en el dia: $%d\n\n\t\t",td);
                               printf("Total vendido en el semana: $%d\n\n\t\t",ts);
                               printf("Total vendido en el mes: $%d\n\n\t\t",tm);
                               system("pause");
                               system("cls");
                               break;
                               
                               
                   case '2':
                        burbujaMasVendidos(x);
                        break;
                        
                   case '3':
                        burbujaMenosVendidos(x);
                        break;
                                         
                   case '4':
                        ok=0;
                        system("cls()");
                        break;
           }
           }while(ok);
           
           fclose(a2);
           fclose(a1);
}



int main(void){ 


int opc;
char opcs; // seleccion Yes or No
int ok2=1;//ok2 para poder inciar una venta
int i=0; //Numero De Asigancion Del Cliente
int x=0;//numero de Asignacion a los articulos
int total=0;//para siempre iniciar una venta en $0
int salir2=1,salir3=1;
int z=0;//contador de la lista de compras
int creacionLista=1;
char pw[50];
char contra1[50],contra2[50];
char pwtekfire[15];
int reset=0;

leerArticulo(&x);
leerClientes(&i);
leerContresania(&creacionLista,pw);
                                                                                                                                                              
color(1); printf("\n\n /))))))))))/");color(3);printf("                  ");color(1);printf("S)3))))))(.");color(3);printf("                      \n");                                
color(1); printf("/))))))))))/");color(3);printf("        S)      ..  ");color(1);printf("))");color(3);printf("                               \n");                      
color(1); printf("    )).");color(3);printf("             ))     3))  ");color(1);printf("))");color(3);printf("          __                   \n");                      
color(1); printf("    ))");color(3);printf("              ))   )3)2   ");color(1);printf("))))))))S");color(3);printf("  /_/                   \n");                  
color(1); printf("    ))");color(3);printf("    s(()))3   )) 3)S3.    ");color(1);printf("))))))))");color(3);printf("        3)S(S)  )$()3S \n");                          
color(1); printf("    ))");color(3);printf("   .))2))9))  ()))S       ");color(1);printf("))).");color(3);printf("       ))  ))33    3)3  3))\n");                          
color(1); printf("    S)");color(3);printf("   ))     B). ))S)3.      ");color(1);printf(")).");color(3);printf("        ))  )).    i)3 .))).\n");                         
color(1); printf("    S)");color(3);printf("   ))   ()S   ))  )3S     ");color(1);printf(")).");color(3);printf("        ))  3)    i)))S))S \n");                          
color(1); printf("    S)");color(3);printf("   )). ))3    S)   .2)3   ");color(1);printf(")).");color(3);printf("        ()  3)     2S-      \n");                         
color(1); printf("    S)");color(3);printf("    )3))(     ))     3(   ");color(1);printf(")).");color(3);printf("        ))  S)      3S.  .. \n");                         
color(1); printf("    3S");color(3);printf("     2)))))i  ))      ()  ");color(1);printf("))");color(3);printf("         ))  ))       (3S))) \n");
color(2); printf("\n\n Producciones.... ");
system("pause");
system("cls");                         
                                                      
 


	do{
       horafecha();
       
       color(1);
	   printf("\n\n\t\t\t* * * * * MENU DE OPCIONES * * * * *");
	   color(2);
       printf("\n\t\t-------------------------------------------------");
       color(1);
       printf("\n\t\t\t TEKFIRE    PRODUCCIONES    PROSTORE");
       color(2);
       printf("\n\t\t-------------------------------------------------\n\n\n");
       color(3);
	   printf("\t\t\t(1) Vender.\n");
       printf("\t\t\t(2) Seccion Vendedor.\n");
	   printf("\t\t\t(3) Seccion Administracion.\n");
	   printf("\t\t\t(4) Seccion Tekfire Tech.\n");
	   printf("\t\t\t(5) Salir.\n");
	   printf("\n\t\tSeleccion: ");
	   
       opc=getch();          
                                
	   system("cls");//limpia la pantalla

       switch(opc)
       {
                
          case '1':
             if(x==0)
             {
				printf("\n\tNo existen articulos registrados\n\n\t");
                system("pause");
                system("cls()");
             }
                
             else
             {              
                 vender(x,&total,&ok2,&z);
                 if(z!=0)
                 {
                    finalizacionDeVenta(x,&total,i,z);
                    total=0;
                    ok2=1;//para poder iniciar la una venta nueva
                    z=0;//nueva lista
                 }
                 
                 else
                 {
					printf("\n\tNo existe el articulo buscado\n\n\t");
					system("pause");
					system("cls()");
                 }                
             }
             break;
            
            //VENDEDOR       
          case '2': 
             do{
				color(1);
				horafecha();
				gotoxy(8,2);
				printf("Menu vendedor.\n");
				color(3);
				printf("\n\n\t\t(1) Ver deuda de un cliente.\n");
				printf("\t\t(2) Agregar cliente a la base de datos.\n");
				printf("\t\t(3) Consultar precio del producto.\n");
				printf("\t\t(4) Abonar dinero a la cuenta de deudas del cliente.\n");
				printf("\t\t(5) Ingresar articulo.\n");
				printf("\t\t(6) Retornar.\n");
				printf("\n\t\tSeleccion: ");
					
              
              opc=getch();          
              
                       
             system("cls");
					
             switch(opc)
             {
                case '1':
                  if(i!=0)
                     verDeuda(i);
                                 
                  else
                  {
                     printf("\n\tNo existe ninguna persona en la base de datos\n");     
                     printf("\n\t");
                     system("pause");
                     system("cls()");
                  }
                  break;
                                 
                case '2':
					nueva(i);
					i++;
					break;
                                 
                case '3':
					if(x==0)
					{
						printf("\n\tNo existen articulos registrados\n");
						printf("\n\t");
						system("pause");
						system("cls()");
					}
                
					else
						consultarPrecio(x);     
					break;
                                 
                case '4':
                  if(i!=0)
                    abonarDinero(i);                  
                  else
                  {
                     printf("\n\tNo existe ninguna persona en la base de datos\n");     
                     printf("\n\t");
                     system("pause");
                     system("cls()");
                  }
                  break;
                       
                case '5'://Ingresar articulo
                   nuevaArticulo(x);
                   x++;
                   break;       
                                 
                case '6':
                  salir2=0;
                  break;
                                 
             }                       
             }while(salir2);
             
             salir2=1;
             break;
		

      //Menu de administracion
         case '3':
             while(creacionLista)
             {
                 creacionContrasenia(contra1,contra2);
                 creacionLista=0;
                 strcpy(pw,contra1);
             }
                
             if(inciarSeccion(pw))
             {
                        
             do{
				color(1);
				horafecha();
				gotoxy(8,2);
				printf("Menu administracion.\n");      
				color(3);
				printf("\n\n\t\t(1) Estadisticas.\n");
				printf("\t\t(2) Modificar articulo.\n");
				printf("\t\t(3) Modificar datos de la persona.\n");
				printf("\t\t(4) Inventario.\n");
				printf("\t\t(5) Borrar cliente.\n");
				printf("\t\t(6) Borrar articulo.\n");
				printf("\t\t(7) Ver lista con todos los clientes y sus respectivos estados.\n");
				printf("\t\t(8) Ver cliente en especifico.\n");
				printf("\t\t(9) Retornar.\n");
				printf("\n\t\tSeleccion: ");
             
				opc=getch();          
                      
				system("cls");
                   
	             switch(opc)
				{
					case '1':
						estadisticas(x);  
						break;
                               
					case '2':
						if(x==0)
						{
							printf("\n\tNo existen articulos registrados\n");
							printf("\n\t");
							system("pause");
							system("cls()");
						}
                
						else
							modificarArticulo(x);
						break;
                               
					case '3':
						if(i!=0)
							modificarCliente(i);                             
						else
						{
							printf("\n\tNo existe ninguna persona en la base de datos\n");     
							printf("\n\t");
							system("pause");
							system("cls()");
						}
						break;
                               
					case '4':
						if(x==0)
						{
							printf("\n\tNo existen articulos registrados\n");
							printf("\n\t");
							system("pause");
							system("cls()");
						}
                
					else
						mostrarInventario(x);     
					break;
                               
					case '5':
						if(i!=0)     
						borrarPersona(&i);
                         
						else      
						{
							printf("\n\tNo existe ninguna persona en la base de datos\n");     
							printf("\n\t");
							system("pause");
							system("cls()");
						}
						break;
                               
					case '6':
						if(x==0)
						{
							printf("\n\tNo existen articulos registrados\n");
							printf("\n\t");
							system("pause");
							system("cls()");
						}		
                
						else
							borrarArticulo(&x);
						break;
                               
					case '7':
						if(i!=0) 
						mostrarLista(i);
                      
						else      
						{
							printf("\n\tNo existe ninguna persona en la base de datos\n");     
							printf("\n\t");
							system("pause");
							system("cls()");
						}
                   break;
                               
                case '8':
                   if(i!=0)
                      verCliente(i);
                               
                   else
                   {
                       printf("\n\tNo existe ninguna persona en la base de datos\n");     
                       printf("\n\t");
                       system("pause");
                       system("cls()");
                   }
                   break;
                                              
                case '9':
                    salir3=0;
                    break;
                    
             }//fin del menu de administrador
       	        
             }while(salir3);
       	        
             salir3=1;
           
             }//Fin del gran if
      
             break;
		
           /*TEKFIRE*/	    
                case '4':
      			   if(iniciarTekfire(pwtekfire))
      			   {
	                system("cls");
				
                   do
                   {
                      color(1);
                      horafecha();
                      gotoxy(8,2);
                      printf("Menu Tekfire.\n");
                      color(3);
                      printf("\n\n\t\t(1) Resetear sistema.\n");
                      printf("\t\t(2) Modificar clave del administrador.\n");
                      printf("\t\t(3) Retornar.\n");
                      printf("\t\t(4) Salir.\n");
                      printf("\n\t\tSeleccion: ");
                      
			          do{
                        
                            opc=getch();          
                        }
                        while(opc>0&&opc<5); 
                
                        system("cls");
                
                      switch(opc)
                      {
                           case '1': 
                                 printf("\n\n\tResetar sistema.\n");
                                 printf("\t\tEsta seguro que desea resetear el sistema? (Y/N)\n");
                                 printf("\t\tADVERTENCIA: Esta accion no puede ser revertida.\n\n");

			          do					
                        {
                            opcs=getch();                                    
                        }
                        while(opcs!='Y'&&opcs!='N'&&opcs!='y'&&opcs!='n'); 
                                 
                                          
                                           switch(opcs)
                                           {
                                                       case 'Y':      //no necesariamente debe ser mayuscula
                                                       case 'y':      //es como 'Y' , 'y' en un mismo case
                                                               
                                                               startzero(&i,&x);
                                                               opc=0;
                                                               reset=1;
                                                               break; 
                                                            
                                                       case 'N':       // idem
                                                       case 'n':       // q vuelva al menu tekfire
																printf("\n\t");
                                                                system("pause");
																system("cls"); 
                                                                break;

                                           }
								 break;

                           case '2':
                                system("cls");
                                creacionContrasenia(contra1,contra2);
                                strcpy(pw,contra1);
                                //break;		Pa q despues de cambiar la contraseña, pase directo al case '3' y se devuelva al menu tekfire
                           case '3':
                                salir2=0;
                                break;

                           case '4':
                                opc=0;
                                break;

                     }          // fin switch
                    
                  }
                  while(opc&&salir2);
            system("cls()");
            
            }
            break;
		
         case '5':
            opc=0;
            break;
            
         }
		        
	}while(opc);

if(reset==0)
{
  guardarCliente(i);
  guardarArticulo(x);
  guardarContrasenia(creacionLista,pw);
  printf("\n\n\tGood Bye""\n\t");
  system("pause");
}

else if(reset==1)
{
  guardarCliente(i);                    
  guardarArticulo(x);
  guardarContrasenia(creacionLista,pw);//es necesario guardar todos los archivos para que al reiniciar se cargen correctamente los datos
  system("start reiniciar.exe");
}

return 0;
}

