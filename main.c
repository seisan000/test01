#include<stdio.h>
#define STAGE_Y_MAX 10
#define STAGE_X_MAX 10
#define N_BLOCK 4
#define HAICHI_TYPE 12
#define FALSE 0
#define TRUE 1
#define BLOCK_TYPE_MAX 4

int mapping(int block[N_BLOCK], int orgin_map[STAGE_Y_MAX][STAGE_X_MAX]);
int hantei(int map[STAGE_Y_MAX][STAGE_X_MAX] ,int y, int x, int type , int num );
int assign(int map[STAGE_Y_MAX][STAGE_X_MAX] ,int y, int x, int type , int num);
int allset(int map[STAGE_Y_MAX][STAGE_X_MAX],int y,int x,int t,int origin_map[STAGE_Y_MAX][STAGE_X_MAX]);
int hyouka(int map[STAGE_Y_MAX][STAGE_X_MAX]);
int hantei2(int map[STAGE_Y_MAX][STAGE_X_MAX] ,int y, int x, int type , int num );
int allset2(int map[STAGE_Y_MAX][STAGE_X_MAX],int y,int x,int origin_map[STAGE_Y_MAX][STAGE_X_MAX],int block[BLOCK_TYPE_MAX]);
int G1;
int score;
int main (void){
	
	int origin_map[STAGE_Y_MAX][STAGE_X_MAX]=
	{
		/*
		{1,0,3,0,0,0,0,0,0,0},
		{0,1,0,0,0,0,0,0,0,0},
		{0,0,2,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0}
		*/
		{1,0,3,0,0,0,0,0,0,0},
		{0,1,0,0,0,0,0,0,0,0},
		{0,0,2,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0}

		/*
		{1,0,3,0,0,0,0,0,0,0},
		{0,1,0,0,0,0,0,0,0,0},
		{0,0,2,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,1,0,0,0},
		{0,0,0,0,0,0,0,1,0,0},
		{0,0,0,0,0,2,3,2,0,0},
		{0,0,0,0,0,0,2,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,3,0,0,0,0,0,0,0,0},
		{0,3,2,1,0,0,0,0,0,0}
		*/
		/*
		{1,1,3,0,0,0,0,0,0,3},
		{0,1,0,0,0,0,3,0,0,2},
		{0,0,2,0,0,0,3,0,0,0},
		{0,0,0,0,0,0,1,0,0,0},
		{0,2,1,0,0,0,0,1,0,0},
		{0,0,0,0,0,2,3,2,0,0},
		{0,0,3,3,0,0,2,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,3,0,0,0,0,3,0,2,0},
		{0,3,2,1,0,0,0,0,0,1}
		*/
	};
	int origin_block[N_BLOCK]={2,2,1,0};
	int i,j;
	G1 = 0;
	
	score = 0;
	for(i = 0; i < N_BLOCK; i++)
	{
		printf("%d ",origin_block[i]);
	}
	printf("\n");

	for(i = 0; i < STAGE_Y_MAX; i++)
	{
		for(j = 0; j < STAGE_X_MAX; j++)
		{
			printf("%d ",origin_map[i][j]);
		}
		printf("\n");

	}
	printf("\n");

	//�����J�n
	 mapping(origin_block, origin_map);



	//���ʕ\��
	for(i = 0; i < STAGE_Y_MAX; i++)
	{
		for(j = 0; j < STAGE_X_MAX; j++)
		{
			printf("%d ",origin_map[i][j]);
		}
		printf("\n");

	}
	printf("\n");
	printf("finish\n");

	return 0;
}


int mapping(int block[N_BLOCK], int origin_map[STAGE_Y_MAX][STAGE_X_MAX])
{
	int result_map[STAGE_Y_MAX][STAGE_X_MAX]={0};
	int y = 2;
	int x = 2;
	int type;
	int num = 2;
	//int block[BLOCK_TYPE_MAX]={4,6,4,4};

	for(y = 0; y < STAGE_Y_MAX; y++)
	{
		for(x = 0; x < STAGE_X_MAX; x++)
		{
			//result_map[y][x] = origin_map[y][x];
		}
	}
	/*
	for(type = 0; type < HAICHI_TYPE; type++)
	{
		printf("type = %d ::",type);
		if(hantei(origin_map,y,x,type,num)){
			printf("mapping�\\n");
		}
		else
		{
			printf("mapping�s�\\n");
		}
	}
	*/

	//allset( origin_map,0,0,0,origin_map);
	/*printf("hyoka = %d\n",hyouka(origin_map));
	for(y = 0; y < 13; y++)
	{
		if(hantei2(origin_map ,9, 9, y, 1) == FALSE)
		{
			printf(" %d\n",y);
		}
	}*/
	if( TRUE == allset2( result_map,0,0,origin_map,block))
	{
		printf("����\n");
	}
	else
	{
		printf("���s\n");
	}
	
	for(y = 0; y < STAGE_Y_MAX; y++)
	{
		for(x = 0; x < STAGE_X_MAX; x++)
		{
			printf("%d ", result_map[y][x]);
		}
		printf("\n");
	}
	printf("\n");

	return TRUE;
}

//�z�u�\�����肷��֐�
int hantei(int map[STAGE_Y_MAX][STAGE_X_MAX] ,int y, int x, int type , int num )
{
	int block1y,block1x;
	int block2y,block2x;
	int i,j;
	int bufy,bufx;
	if(type > 12 || type < 0)
	{
		return FALSE;
	}

	if(y >= STAGE_Y_MAX || y < 0)
	{
		return FALSE;
	}
	if(x >= STAGE_X_MAX || x < 0)
	{
		return FALSE;
	}
	//printf("start ");
	//printf("y=%d x=%d ", y,x);
	//printf("map=%d num=%d ", map[y][x],num);
	//if(map[y][x] == 0)printf("0 ");
	//if(map[y][x] == num) printf("num ");
	if((map[y][x] == 0) || (map[y][x] == num) )
	{
		//printf("ok  x y ");
		switch (type)
		{
		case 0:
			//   1
			//   ��2
			//
			block1y = y -1;
			block1x = x;
			block2y = y;
			block2x = x + 1;
			if(block1y < 0 || block1x < 0 || block1y >= STAGE_Y_MAX || block1x >= STAGE_X_MAX || block2y < 0 || block2x < 0 || block2y >= STAGE_Y_MAX || block2x >= STAGE_X_MAX )
			{
				return FALSE;
			}
			
			break;
		case 1:
			//   
			//   ��1
			//   2
			block1y = y;
			block1x = x + 1;
			block2y = y + 1;
			block2x = x;
			if(block1y < 0 || block1x < 0 || block1y >= STAGE_Y_MAX || block1x >= STAGE_X_MAX || block2y < 0 || block2x < 0 || block2y >= STAGE_Y_MAX || block2x >= STAGE_X_MAX )
			{
				return FALSE;
			}
			
			break;
		case 2:
			//   
			//  2��
			//   1
			block1y = y + 1;
			block1x = x;
			block2y = y;
			block2x = x - 1;
			if(block1y < 0 || block1x < 0 || block1y >= STAGE_Y_MAX || block1x >= STAGE_X_MAX || block2y < 0 || block2x < 0 || block2y >= STAGE_Y_MAX || block2x >= STAGE_X_MAX )
			{
				return FALSE;
			}
			
			break;
		case 3:
			//   1
			//  2��
			//   
			block1y = y - 1;
			block1x = x;
			block2y = y;
			block2x = x - 1;
			if(block1y < 0 || block1x < 0 || block1y >= STAGE_Y_MAX || block1x >= STAGE_X_MAX || block2y < 0 || block2x < 0 || block2y >= STAGE_Y_MAX || block2x >= STAGE_X_MAX )
			{
				return FALSE;
			}
			
			break;
		case 4:
			//   
			//   ��
			//   1  2
			block1y = y + 1;
			block1x = x ;
			block2y = y + 1;
			block2x = x + 1;
			if(block1y < 0 || block1x < 0 || block1y >= STAGE_Y_MAX || block1x >= STAGE_X_MAX || block2y < 0 || block2x < 0 || block2y >= STAGE_Y_MAX || block2x >= STAGE_X_MAX )
			{
				return FALSE;
			}
			
			break;
		case 5:
			//   
			// 1 ��
			// 2    
			block1y = y;
			block1x = x - 1;
			block2y = y + 1;
			block2x = x - 1;
			if(block1y < 0 || block1x < 0 || block1y >= STAGE_Y_MAX || block1x >= STAGE_X_MAX || block2y < 0 || block2x < 0 || block2y >= STAGE_Y_MAX || block2x >= STAGE_X_MAX )
			{
				return FALSE;
			}
			
			break;
		case 6:
			// 2 1
			//   ��
			//   
			block1y = y - 1;
			block1x = x;
			block2y = y - 1;
			block2x = x - 1;
			if(block1y < 0 || block1x < 0 || block1y >= STAGE_Y_MAX || block1x >= STAGE_X_MAX || block2y < 0 || block2x < 0 || block2y >= STAGE_Y_MAX || block2x >= STAGE_X_MAX )
			{
				return FALSE;
			}
			
			break;
		case 7:
			//     2
			//   ��1
			//   
			block1y = y;
			block1x = x + 1;
			block2y = y - 1;
			block2x = x + 1;
			if(block1y < 0 || block1x < 0 || block1y >= STAGE_Y_MAX || block1x >= STAGE_X_MAX || block2y < 0 || block2x < 0 || block2y >= STAGE_Y_MAX || block2x >= STAGE_X_MAX )
			{
				return FALSE;
			}
			
			break;
		case 8:
			//   
			//   ��
			// 2 1  
			block1y = y + 1;
			block1x = x;
			block2y = y + 1;
			block2x = x - 1;
			if(block1y < 0 || block1x < 0 || block1y >= STAGE_Y_MAX || block1x >= STAGE_X_MAX || block2y < 0 || block2x < 0 || block2y >= STAGE_Y_MAX || block2x >= STAGE_X_MAX )
			{
				return FALSE;
			}
			
			break;
		case 9:
			//   
			//   ��1
			//     2
			block1y = y;
			block1x = x + 1;
			block2y = y + 1;
			block2x = x + 1;
			if(block1y < 0 || block1x < 0 || block1y >= STAGE_Y_MAX || block1x >= STAGE_X_MAX || block2y < 0 || block2x < 0 || block2y >= STAGE_Y_MAX || block2x >= STAGE_X_MAX )
			{
				return FALSE;
			}
			
			break;
		case 10:
			//   1 2
			//   ��
			//     
			block1y = y - 1;
			block1x = x;
			block2y = y - 1;
			block2x = x + 1;
			if(block1y < 0 || block1x < 0 || block1y >= STAGE_Y_MAX || block1x >= STAGE_X_MAX || block2y < 0 || block2x < 0 || block2y >= STAGE_Y_MAX || block2x >= STAGE_X_MAX )
			{
				return FALSE;
			}
			
			break;
		case 11:
			// 2  
			// 1 ��
			//     
			block1y = y;
			block1x = x - 1;
			block2y = y - 1;
			block2x = x - 1;
			if(block1y < 0 || block1x < 0 || block1y >= STAGE_Y_MAX || block1x >= STAGE_X_MAX || block2y < 0 || block2x < 0 || block2y >= STAGE_Y_MAX || block2x >= STAGE_X_MAX )
			{
				return FALSE;
			}
		
			break;
		default:
				return FALSE;
			break;

		}
		//�`�F�b�N�Ώۃu���b�N���z�u�\������
		if((map[block1y][block1x] == 0 || map[block1y][block1x] == num) && (map[block2y][block2x] == 0 || map[block2y][block2x] == num) ){
		}
		else
		{
			return FALSE;
		}


		
		//�`�F�b�N�Ώۂ̃u���b�N�ɗאڂ���u���b�N�ɓ���i���o�[���Ȃ����m�F
		for(i = 0; i < 3; i++)
		{
			if( i == 0)
			{
				bufy = y;
				bufx = x;
			}
			else if( i == 1)
			{
				bufy = block1y;
				bufx = block1x;
			}
			else if( i == 2)
			{
				bufy = block2y;
				bufx = block2x;
			}
			
			if(bufy-1 >= 0)
			{
				if(map[bufy-1][bufx] == num)
				{
					//printf("1 ");
					if(!((bufy-1 == y && bufx == x) || (bufy-1 == block1y && bufx == block1x) || (bufy-1 == block2y && bufx == block2x) ))
					{
						return FALSE;
					}
				}
			}
			if(bufx+1 < STAGE_X_MAX)
			{
				if(map[bufy][bufx+1] == num)
				{
					//printf("2 ");
					if(!((bufy == y && bufx+1 == x) || (bufy == block1y && bufx + 1 == block1x) || (bufy == block2y && bufx + 1 == block2x)) ){
						return FALSE;
					}
				}
			}

			if(bufy+1 < STAGE_Y_MAX)
			{
				if(map[bufy+1][bufx] == num)
				{
					//printf("3 ");
					if(!((bufy+1 == y && bufx == x) || (bufy+1 == block1y && bufx == block1x) || (bufy+1 == block2y && bufx == block2x)) ){
						return FALSE;
					}
				}
			}

			if(bufx-1 >= 0)
			{
				if(map[bufy][bufx-1] == num)
				{
					//printf("4 ");
					if(!((bufy == y && bufx-1 == x) || (bufy == block1y && bufx-1 == block1x) || (bufy == block2y && bufx-1 == block2x)) ){
						return FALSE;
					}
				}
			}
		}

		return TRUE;


	}
	else
	{
		return FALSE;
	}

	//return FALSE;
	
}

int assign(int map[STAGE_Y_MAX][STAGE_X_MAX] ,int y, int x, int type , int num)
{
	int block1y,block1x,block2y,block2x;

	switch (type)
		{
		case 0:
			//   1
			//   ��2
			//
			block1y = y -1;
			block1x = x;
			block2y = y;
			block2x = x + 1;
		
			
			break;
		case 1:
			//   
			//   ��1
			//   2
			block1y = y;
			block1x = x + 1;
			block2y = y + 1;
			block2x = x;
			
			
			break;
		case 2:
			//   
			//  2��
			//   1
			block1y = y + 1;
			block1x = x;
			block2y = y;
			block2x = x - 1;
			
			
			break;
		case 3:
			//   1
			//  2��
			//   
			block1y = y - 1;
			block1x = x;
			block2y = y;
			block2x = x - 1;
			
			
			break;
		case 4:
			//   
			//   ��
			//   1  2
			block1y = y + 1;
			block1x = x ;
			block2y = y + 1;
			block2x = x + 1;
			
			
			break;
		case 5:
			//   
			// 1 ��
			// 2    
			block1y = y;
			block1x = x - 1;
			block2y = y + 1;
			block2x = x - 1;
			
			
			break;
		case 6:
			// 2 1
			//   ��
			//   
			block1y = y - 1;
			block1x = x;
			block2y = y - 1;
			block2x = x - 1;
			
			
			break;
		case 7:
			//     2
			//   ��1
			//   
			block1y = y;
			block1x = x + 1;
			block2y = y - 1;
			block2x = x + 1;
			
			
			break;
		case 8:
			//   
			//   ��
			// 2 1  
			block1y = y + 1;
			block1x = x;
			block2y = y + 1;
			block2x = x - 1;
			
			
			break;
		case 9:
			//   
			//   ��1
			//     2
			block1y = y;
			block1x = x + 1;
			block2y = y + 1;
			block2x = x + 1;
			
			
			break;
		case 10:
			//   1 2
			//   ��
			//     
			block1y = y - 1;
			block1x = x;
			block2y = y - 1;
			block2x = x + 1;
			
			break;
		case 11:
			// 2  
			// 1 ��
			//     
			block1y = y;
			block1x = x - 1;
			block2y = y - 1;
			block2x = x - 1;
			
			break;
		case 12:
			//    
			//   �����z�u���Ȃ�
			//     
			//block1y = -1;
			//block1x = -1;
			//block2y = -1;
			//block2x = -1;
			return TRUE;
			break;

		default:
				return FALSE;
			break;

		}
		
		map[block1y][block1x] = num;
		map[block2y][block2x] = num;
		map[y][x] = num;

		return TRUE;
		
}
//����u���b�N�z�u�֐�
int allset(int map[STAGE_Y_MAX][STAGE_X_MAX],int y,int x,int t,int origin_map[STAGE_Y_MAX][STAGE_X_MAX])
{
	int i,j;
	int posY,posX,type;
	int bufx=0;

	int sub_map[STAGE_Y_MAX][STAGE_X_MAX]={0};
	
	//�]��
	for(i = 0; i < STAGE_Y_MAX; i++)
	{
		for(j = 0; j < STAGE_X_MAX; j++)
		{
			sub_map[i][j] = map[i][j];
		}
	}
	G1++;
	bufx = x;
	for(posY = y; posY < STAGE_Y_MAX; posY++)
	{
		for(posX = bufx; posX < STAGE_X_MAX; posX++)
		{
			//�I���W�i���̍��W������Ώۂɂ���
			if(origin_map[posY][posX] != 0)
			{
				
				for(type = t; type < HAICHI_TYPE; type++)
				{
					if(hantei(sub_map,posY,posX,type,sub_map[posY][posX]))
					{
						
						//������
						assign(sub_map,posY,posX,type,sub_map[posY][posX]);
						//printf("allset\n");
						if(FALSE == allset(sub_map,posY,posX + 1,0,origin_map))
						{
							//���s���}�b�v����
							for(i = 0; i < STAGE_Y_MAX; i++)
							{
								for(j = 0; j < STAGE_X_MAX; j++)
								{
									sub_map[i][j] = map[i][j];
								}
							}
						}
						else
						{
							//������
							for(i = 0; i < STAGE_Y_MAX; i++)
							{
								for(j = 0; j < STAGE_X_MAX; j++)
								{
									 map[i][j] = sub_map[i][j];
								}
							}
							//break;
							return TRUE;
						}
						

						
						//break;
					}
					
				}

				if(type == HAICHI_TYPE){
					//allset(map,posY,posX,type);
					/*
					printf("backtrack\n");
					printf("posy=%d posx=%d \n",posY,posX);
					for(i = 0; i < STAGE_Y_MAX; i++)
					{
						for(j = 0; j < STAGE_X_MAX; j++)
						{
							printf("%d ",sub_map[i][j]);
						}
						printf("\n");
					}
					printf("\n");
					*/

					return FALSE;
				}
			}//
		}
		bufx = 0;
	}
	/*
	for(i = 0; i < STAGE_Y_MAX; i++)
	{
		for(j = 0; j < STAGE_X_MAX; j++)
		{
			printf("%d ",map[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	*/
	//�ύX��}�b�v���f
	

	return TRUE;
}

//�]���֐�
int hyouka(int map[STAGE_Y_MAX][STAGE_X_MAX]){
	int i,j;
	int score = 0;

	for(i = 0;i<STAGE_Y_MAX; i++)
	{
		for(j = 0;j < STAGE_X_MAX;j++)
		{
			if(j < STAGE_X_MAX - 1)
			{
				if(map[i][j] != 0 && map[i][j+1] != 0)
				{
					//printf("%d %d:%d %d    \n",i,j,i,j+1);
					score++;
				}
			}
			if( i < STAGE_Y_MAX -1 )
			{
				if(map[i][j] != 0 && map[i+1][j] != 0)
				{
					//printf("%d %d:%d %d    \n",i,j,i+1,j);
					score++;
				}
			}
		}

	}
	return score;

}

//�񐧖�u���b�N�z�u�֐�

int allset2(int sub_map[STAGE_Y_MAX][STAGE_X_MAX],int y,int x,int origin_map[STAGE_Y_MAX][STAGE_X_MAX],int block[BLOCK_TYPE_MAX])
{
	int i,j;
	int posY,posX,type;
	int bufx=0;
	int n_block;
	int color;
	int n_color;
	int buf_block[BLOCK_TYPE_MAX];
	//int block[BLOCK_TYPE_MAX];
	//int sub_map[STAGE_Y_MAX][STAGE_X_MAX]={0};
	int sub_map2[STAGE_Y_MAX][STAGE_X_MAX]={0};
	int buf_map[STAGE_Y_MAX][STAGE_X_MAX]={0};
	
	//G1++;
	bufx = x;
	for(posY = y; posY < STAGE_Y_MAX; posY++)
	{
		
		for(posX = bufx; posX < STAGE_X_MAX; posX+=2)
		{
			/*for(color = 0,n_color = 0; color < BLOCK_TYPE_MAX; color++)
			{
				n_color += block[color];
			}
			if( n_color == 0 )
			{
				return FALSE;
			}*/

			////�u���b�N���g���؂������I�������𖞂����Ă��邩�m�F
			//for(color = 0,n_color = 0; color < BLOCK_TYPE_MAX; color++)
			//{
			//	n_color += buf_block[color];
			//}
			//if(n_color == 0 )
			//{
			//	printf("xx0\n");
			//	if(TRUE == finishcheck(map, origin_map,buf_block))
			//	{
			//		printf("FINISH map\n");
			//		for(i = 0; i < STAGE_Y_MAX; i++)
			//		{
			//			for(j = 0; j < STAGE_X_MAX; j++)
			//			{
			//				printf("%d ",sub_map[i][j]);
			//			}
			//			printf("\n");
			//		}
			//		printf("\n");
			//		return TRUE;
			//	}
			//}

			//�z�u�w�肪����Ƃ��͕K�������Ă�
			if(origin_map[posY][posX] != sub_map[posY][posX] && origin_map[posY][posX] != 0 )
			{
				
					//���łɔz�u����Ă���Ƃ��̓X�L�b�v

					//�u���b�N���Ȃ��Ƃ��͒��~
					for(color = 0,n_color = 0; color < BLOCK_TYPE_MAX; color++)
					{
						n_color += block[color];
					}
					if( n_color <= 0 )
					{
						return FALSE;
					}
					if( block[origin_map[posY][posX]-1] <= 0 )
					{
						//printf("block[%d] = %d\n", origin_map[posY][posX]-1, block[origin_map[posY][posX]-1]);
						return FALSE;
					}

				
					//�]��
					for(i = 0; i < STAGE_Y_MAX; i++)
					{
						for(j = 0; j < STAGE_X_MAX; j++)
						{
							buf_map[i][j] = sub_map[i][j];
						}
					}

					for(i = 0; i < BLOCK_TYPE_MAX; i++)
					{
						buf_block[i] = block[i];
					}

					for(type = 0; type < HAICHI_TYPE; type++)
					{
						if(hantei2(sub_map,posY,posX,type,origin_map[posY][posX]) )
						{
						
							//printf("�w�� before\n");
							//for(i = 0; i < STAGE_Y_MAX; i++)
							//{
							//	for(j = 0; j < STAGE_X_MAX; j++)
							//	{
							//		printf("%d ",buf_map[i][j]);
							//	}
							//	printf("\n");
							//}
							//printf("posx=%d posy=%d type =%d color= %d\n",posX,posY,type,origin_map[posY][posX]);
							//
							//�w����W�ƌ��ݔz�u�𔽉f�����}�b�v�쐻
							for(i = 0; i < STAGE_Y_MAX; i++)
							{
								for(j = 0; j < STAGE_X_MAX; j++)
								{
									//if(origin_map[i][j] != 0)
									//{
										buf_map[i][j] = sub_map[i][j];
									//}
								}
							}
							for(i = 0; i < BLOCK_TYPE_MAX; i++)
							{
								buf_block[i] = block[i];
							}
							//������
							assign(sub_map,posY,posX,type,origin_map[posY][posX]);

							//printf("�w�� after\n");
							//for(i = 0; i < STAGE_Y_MAX; i++)
							//{
							//	for(j = 0; j < STAGE_X_MAX; j++)
							//	{
							//		printf("%d ",sub_map[i][j]);
							//	}
							//	printf("\n");
							//}
						

							
							block[origin_map[posY][posX]-1]--;
							
							//printf("�w�� ");
							//printf("%d�g�p\n\n",origin_map[posY][posX]);
							//printf("allset\n");
							if(FALSE == allset2(sub_map,posY,posX + 1,origin_map,block))
							{
								//���s���}�b�v����
								for(i = 0; i < STAGE_Y_MAX; i++)
								{
									for(j = 0; j < STAGE_X_MAX; j++)
									{
										sub_map[i][j] = buf_map[i][j];
									}
								}
								//block����
								for(i = 0; i < BLOCK_TYPE_MAX; i++)
								{
										block[i] = buf_block[i];
								}
								//printf("shitei false\n");
								//return FALSE;
							}
							else
							{
								//break;
								return TRUE;
							}

						}
					
					}
					return FALSE;
				
				
			}
			else//�w��z�u����Ȃ��Ƃ�
			{
				
				for(color = 0; color < BLOCK_TYPE_MAX; color++)
				{
					if(block[color] > 0 )
					{
						//printf("\n");

						for(type = 0; type < HAICHI_TYPE+1; type++)
						{
							if(hantei2(sub_map,posY,posX,type,color+1))
							{
								//
								//�w����W�ƌ��ݔz�u�𔽉f�����}�b�v�쐻
								for(i = 0; i < STAGE_Y_MAX; i++)
								{
									for(j = 0; j < STAGE_X_MAX; j++)
									{
										//if(origin_map[i][j] != 0)
										//{
											buf_map[i][j] = sub_map[i][j];
										//}
									}
								}
								for(i = 0; i < BLOCK_TYPE_MAX; i++)
								{
									buf_block[i] = block[i];
								}
								//printf(" before\n");
								//for(i = 0; i < STAGE_Y_MAX; i++)
								//{
								//	for(j = 0; j < STAGE_X_MAX; j++)
								//	{
								//		printf("%d ",sub_map[i][j]);
								//	}
								//	printf("\n");
								//}
								//printf("posx=%d posy=%d type =%d color= %d\n",posX,posY,type,color+1);
								//
					
								//������
								assign(sub_map,posY,posX,type,color+1);


								//printf(" after\n");
								//for(i = 0; i < STAGE_Y_MAX; i++)
								//{
								//	for(j = 0; j < STAGE_X_MAX; j++)
								//	{
								//		printf("%d ",sub_map[i][j]);
								//	}
								//	printf("\n");
								//}
								//

								if(!(type == HAICHI_TYPE))
								{
									block[color]--;
								}
								//printf("%d�g�p\n\n",color+1);
								//printf("allset\n");
								if(FALSE == allset2(sub_map,posY,posX + 1,origin_map,block))
								{
									//���s���}�b�v����
									for(i = 0; i < STAGE_Y_MAX; i++)
									{
										for(j = 0; j < STAGE_X_MAX; j++)
										{
											sub_map[i][j] = buf_map[i][j];
										}
									}
									//block����
									for(i = 0; i < BLOCK_TYPE_MAX; i++)
									{
										 block[i] = buf_block[i];
									}
									
								}
								else
								{
									//break;

									return TRUE;
								}
						

						
								//break;
							}
					
						}
						/*
						if(type == HAICHI_TYPE){
							//allset(map,posY,posX,type);
						
							//���s���}�b�v����
							for(i = 0; i < STAGE_Y_MAX; i++)
							{
								for(j = 0; j < STAGE_X_MAX; j++)
								{
									sub_map[i][j] = map[i][j];
								}
							}
							//block����
							for(i = 0; i < BLOCK_TYPE_MAX; i++)
							{
									buf_block[i] = block[i];
							}

							return FALSE;
						}
						*/
					}
				}
			}

			//�u���b�N���Ȃ��Ƃ�
			n_block = 0;
			for( i = 0; i < BLOCK_TYPE_MAX; i++)
			{
				n_block += block[i];
			}
			if( n_block <= 0)
			{

				//���܂��Ă��Ȃ��ꏊ�͂Ȃ����H
				for(i = 0; i < STAGE_Y_MAX; i++)
				{
					for(j = 0; j < STAGE_X_MAX; j++)
					{
						//1�ł����܂��ĂȂ��ꏊ����������I��
						if((sub_map[i][j] & origin_map[i][j]) != origin_map[i][j] )
						{
							printf("BACK TRACK!!!!\n");
							return FALSE;
						}
					}
					//printf("\n");
				}
			
				printf("COMPLEAT FINISH map!!\n");
				for(i = 0; i < STAGE_Y_MAX; i++)
				{
					for(j = 0; j < STAGE_X_MAX; j++)
					{
						printf("%d ",sub_map[i][j]);
					}
					printf("\n");
				}
				printf("\n");
			
				/*
				printf("FINISH orign_map\n");
				for(i = 0; i < STAGE_Y_MAX; i++)
				{
					for(j = 0; j < STAGE_X_MAX; j++)
					{
						printf("%d ",origin_map[i][j]);
					}
					printf("\n");
				}
				printf("\n");
				printf("score = %d\n", hyouka(sub_map));
				*/

				//������
				
				//break;
				return TRUE;
				//score�`�F�b�N
				if( score < hyouka(sub_map)){
					score = hyouka(sub_map);
				}
				//map(0,0) != 0?

				//�Ǘ��u���b�N�͂Ȃ����H
			}
	
		}//posX
		
		
		bufx = 0;
	}
	n_block = 0;
	for( i = 0; i < BLOCK_TYPE_MAX; i++)
	{
		printf("%d = %d\n",i+1,block[i]);
		n_block += block[i];
	}

	
	for(i = 0; i < STAGE_Y_MAX; i++)
	{
		for(j = 0; j < STAGE_X_MAX; j++)
		{
			printf("%d ",sub_map[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	
	//�ύX��}�b�v���f
	
	printf("xx11\n");
	return FALSE;
}

//�w��Ȃ��u���b�N��z�u���邩���肷��֐�
int hantei2(int map[STAGE_Y_MAX][STAGE_X_MAX] ,int y, int x, int type , int num )
{
	int block1y,block1x;
	int block2y,block2x;
	int i,j;
	int bufy,bufx;
	int check = 0;

	if(type == 12){
		//�u����Ƃ��ȑO�Ɏ��̂��Ȃ�����
		//printf("����u�����Ƃ��Ă����\n");
		return TRUE;
	}

	if(type < 0)
	{
		return FALSE;
	}

	if(y >= STAGE_Y_MAX || y < 0)
	{
		return FALSE;
	}
	if(x >= STAGE_X_MAX || x < 0)
	{
		return FALSE;
	}
	//printf("start ");
	//printf("y=%d x=%d ", y,x);
	//printf("map=%d num=%d ", map[y][x],num);
	//if(map[y][x] == 0)printf("0 ");
	//if(map[y][x] == num) printf("num ");
	if((map[y][x] == 0) || (map[y][x] == num) )
	{
		//printf("ok  x y ");
		switch (type)
		{
		case 0:
			//   1
			//   ��2
			//
			block1y = y -1;
			block1x = x;
			block2y = y;
			block2x = x + 1;
			if(block1y < 0 || block1x < 0 || block1y >= STAGE_Y_MAX || block1x >= STAGE_X_MAX || block2y < 0 || block2x < 0 || block2y >= STAGE_Y_MAX || block2x >= STAGE_X_MAX )
			{
				return FALSE;
			}
			
			break;
		case 1:
			//   
			//   ��1
			//   2
			block1y = y;
			block1x = x + 1;
			block2y = y + 1;
			block2x = x;
			if(block1y < 0 || block1x < 0 || block1y >= STAGE_Y_MAX || block1x >= STAGE_X_MAX || block2y < 0 || block2x < 0 || block2y >= STAGE_Y_MAX || block2x >= STAGE_X_MAX )
			{
				return FALSE;
			}
			
			break;
		case 2:
			//   
			//  2��
			//   1
			block1y = y + 1;
			block1x = x;
			block2y = y;
			block2x = x - 1;
			if(block1y < 0 || block1x < 0 || block1y >= STAGE_Y_MAX || block1x >= STAGE_X_MAX || block2y < 0 || block2x < 0 || block2y >= STAGE_Y_MAX || block2x >= STAGE_X_MAX )
			{
				return FALSE;
			}
			
			break;
		case 3:
			//   1
			//  2��
			//   
			block1y = y - 1;
			block1x = x;
			block2y = y;
			block2x = x - 1;
			if(block1y < 0 || block1x < 0 || block1y >= STAGE_Y_MAX || block1x >= STAGE_X_MAX || block2y < 0 || block2x < 0 || block2y >= STAGE_Y_MAX || block2x >= STAGE_X_MAX )
			{
				return FALSE;
			}
			
			break;
		case 4:
			//   
			//   ��
			//   1  2
			block1y = y + 1;
			block1x = x ;
			block2y = y + 1;
			block2x = x + 1;
			if(block1y < 0 || block1x < 0 || block1y >= STAGE_Y_MAX || block1x >= STAGE_X_MAX || block2y < 0 || block2x < 0 || block2y >= STAGE_Y_MAX || block2x >= STAGE_X_MAX )
			{
				return FALSE;
			}
			
			break;
		case 5:
			//   
			// 1 ��
			// 2    
			block1y = y;
			block1x = x - 1;
			block2y = y + 1;
			block2x = x - 1;
			if(block1y < 0 || block1x < 0 || block1y >= STAGE_Y_MAX || block1x >= STAGE_X_MAX || block2y < 0 || block2x < 0 || block2y >= STAGE_Y_MAX || block2x >= STAGE_X_MAX )
			{
				return FALSE;
			}
			
			break;
		case 6:
			// 2 1
			//   ��
			//   
			block1y = y - 1;
			block1x = x;
			block2y = y - 1;
			block2x = x - 1;
			if(block1y < 0 || block1x < 0 || block1y >= STAGE_Y_MAX || block1x >= STAGE_X_MAX || block2y < 0 || block2x < 0 || block2y >= STAGE_Y_MAX || block2x >= STAGE_X_MAX )
			{
				return FALSE;
			}
			
			break;
		case 7:
			//     2
			//   ��1
			//   
			block1y = y;
			block1x = x + 1;
			block2y = y - 1;
			block2x = x + 1;
			if(block1y < 0 || block1x < 0 || block1y >= STAGE_Y_MAX || block1x >= STAGE_X_MAX || block2y < 0 || block2x < 0 || block2y >= STAGE_Y_MAX || block2x >= STAGE_X_MAX )
			{
				return FALSE;
			}
			
			break;
		case 8:
			//   
			//   ��
			// 2 1  
			block1y = y + 1;
			block1x = x;
			block2y = y + 1;
			block2x = x - 1;
			if(block1y < 0 || block1x < 0 || block1y >= STAGE_Y_MAX || block1x >= STAGE_X_MAX || block2y < 0 || block2x < 0 || block2y >= STAGE_Y_MAX || block2x >= STAGE_X_MAX )
			{
				return FALSE;
			}
			
			break;
		case 9:
			//   
			//   ��1
			//     2
			block1y = y;
			block1x = x + 1;
			block2y = y + 1;
			block2x = x + 1;
			if(block1y < 0 || block1x < 0 || block1y >= STAGE_Y_MAX || block1x >= STAGE_X_MAX || block2y < 0 || block2x < 0 || block2y >= STAGE_Y_MAX || block2x >= STAGE_X_MAX )
			{
				return FALSE;
			}
			
			break;
		case 10:
			//   1 2
			//   ��
			//     
			block1y = y - 1;
			block1x = x;
			block2y = y - 1;
			block2x = x + 1;
			if(block1y < 0 || block1x < 0 || block1y >= STAGE_Y_MAX || block1x >= STAGE_X_MAX || block2y < 0 || block2x < 0 || block2y >= STAGE_Y_MAX || block2x >= STAGE_X_MAX )
			{
				return FALSE;
			}
			
			break;
		case 11:
			// 2  
			// 1 ��
			//     
			block1y = y;
			block1x = x - 1;
			block2y = y - 1;
			block2x = x - 1;
			if(block1y < 0 || block1x < 0 || block1y >= STAGE_Y_MAX || block1x >= STAGE_X_MAX || block2y < 0 || block2x < 0 || block2y >= STAGE_Y_MAX || block2x >= STAGE_X_MAX )
			{
				return FALSE;
			}
		
			break;
		default:
				return FALSE;
			break;

		}
		//�`�F�b�N�Ώۃu���b�N���z�u�\������
		if((map[block1y][block1x] == 0 || map[block1y][block1x] == num) && (map[block2y][block2x] == 0 || map[block2y][block2x] == num) ){
		}
		else
		{
			return FALSE;
		}


		
		//�`�F�b�N�Ώۂ̃u���b�N�ɗאڂ���u���b�N�ɓ���i���o�[���Ȃ����m�F
		for(i = 0; i < 3; i++)
		{
			if( i == 0)
			{
				bufy = y;
				bufx = x;
			}
			else if( i == 1)
			{
				bufy = block1y;
				bufx = block1x;
			}
			else if( i == 2)
			{
				bufy = block2y;
				bufx = block2x;
			}
			
			if(bufy-1 >= 0)
			{
				if(map[bufy-1][bufx] == num)
				{
					//printf("1 ");
					if(!((bufy-1 == y && bufx == x) || (bufy-1 == block1y && bufx == block1x) || (bufy-1 == block2y && bufx == block2x) ))
					{
						return FALSE;
					}
				}
			}
			if(bufx+1 < STAGE_X_MAX)
			{
				if(map[bufy][bufx+1] == num)
				{
					//printf("2 ");
					if(!((bufy == y && bufx+1 == x) || (bufy == block1y && bufx + 1 == block1x) || (bufy == block2y && bufx + 1 == block2x)) ){
						return FALSE;
					}
				}
			}

			if(bufy+1 < STAGE_Y_MAX)
			{
				if(map[bufy+1][bufx] == num)
				{
					//printf("3 ");
					if(!((bufy+1 == y && bufx == x) || (bufy+1 == block1y && bufx == block1x) || (bufy+1 == block2y && bufx == block2x)) ){
						return FALSE;
					}
				}
			}

			if(bufx-1 >= 0)
			{
				if(map[bufy][bufx-1] == num)
				{
					//printf("4 ");
					if(!((bufy == y && bufx-1 == x) || (bufy == block1y && bufx-1 == block1x) || (bufy == block2y && bufx-1 == block2x)) ){
						return FALSE;
					}
				}
			}
		}

		//�Ǘ����Ă��Ă����W00�Ȃ�OK
		for(i = 0; i < 3; i++)
		{
			if( i == 0)
			{
				bufy = y;
				bufx = x;
			}
			else if( i == 1)
			{
				bufy = block1y;
				bufx = block1x;
			}
			else if( i == 2)
			{
				bufy = block2y;
				bufx = block2x;
			}
			if(bufy == 0 && bufx == 0)
			{
				printf("0,0�ɂ���̂ŃZ�[�t\n");
				return TRUE;
			}
			
		}


		//�Ǘ��u���b�N�ł͂Ȃ����m�F
		if(!((y == 0 && x== 0) || (block1y == 0 && block1x== 0) || (block2y == 0 && block2x== 0)) )
		{
			check = 0;
			//�Ώۍ��W
			if((!(y-1 == block1y && x == block1x) && !(y-1 == block2y && x == block2x)) )
			{
				if(y-1 >= 0 )
				if(!(map[y-1][x] == 0))
				{
					check++;
				
				}
			}
			if((!(y == block1y && x + 1 == block1x) && !(y == block2y && x + 1 == block2x)) )
			{
				if(x+1 < STAGE_X_MAX )
				if(!(map[y][x+1] == 0))
				{
					check++;
				
				}
			}
			if((!(y+1 == block1y && x == block1x) && !(y+1 == block2y && x == block2x)) )
			{
				if(y+1 < STAGE_Y_MAX )
				if(!(map[y+1][x] == 0))
				{
					check++;
				
				}
			}
			if((!(y == block1y && x-1 == block1x) && !(y == block2y && x-1 == block2x)) )
			{
				if(x-1 >= 0 )
				if(!(map[y][x-1] == 0))
				{
					check++;
				
				}
			}
			//block1
			if((!(block1y-1 == y && block1x == x) && !(block1y-1 == block2y && block1x == block2x)) )
			{
				if(block1y-1 >= 0 )
				if(!(map[block1y-1][block1x] == 0))
				{
					check++;
				
				}
			}
			if((!(block1y == y && block1x + 1 == x) && !(block1y == block2y && block1x + 1 == block2x)) )
			{
				if(block1x+1 < STAGE_X_MAX )
				if(!(map[block1y][block1x+1] == 0))
				{
					check++;
				
				}
			}
			if((!(block1y+1 == y && block1x == x) && !(block1y+1 == block2y && block1x == block2x)) )
			{
				if(block1y+1 < STAGE_Y_MAX )
				if(!(map[block1y+1][block1x] == 0))
				{
					check++;
				
				}
			}
			if((!(block1y == y && block1x-1 == x) && !(block1y == block2y && block1x-1 == block2x)) )
			{
				if(block1x-1 >= 0 )
				if(!(map[block1y][block1x-1] == 0))
				{
					check++;
				
				}
			}
			//block2
			if((!(block2y-1 == y && block2x == x) && !(block2y-1 == block1y && block2x == block1x)) )
			{
				if(block2y-1 >= 0 )
				if(!(map[block2y-1][block2x] == 0))
				{
					check++;
				
				}
			}
			if((!(block2y == y && block2x + 1 == x) && !(block2y == block1y && block2x + 1 == block1x)) )
			{
				if(block2y+1 >= STAGE_X_MAX )
				if(!(map[block2y][block2x+1] == 0))
				{
					check++;
				
				}
			}
			if((!(block2y+1 == y && block2x == x) && !(block2y+1 == block1y && block2x == block1x)) )
			{
				if(block1y+1 >= STAGE_Y_MAX)
				if(!(map[block2y+1][block2x] == 0))
				{
					check++;
				
				}
			}
			if((!(block2y == y && block2x-1 == x) && !(block2y == block1y && block2x-1 == block1x)) )
			{
				if(block2x-1 >= 0 )
				if(!(map[block2y][block2x-1] == 0))
				{
				
					check++;
				}
			}
			if(check == 0)
			{
				//printf("�Ǘ�a\n");
				return FALSE;
			}
		}
			










		return TRUE;


	}
	else
	{
		return FALSE;
	}

	//return FALSE;
	
}

//�c��u���b�N���Ŕ��肷��֐���ǉ�

//�������Ă��邩�`�F�b�N�֐�
int finishcheck(int map[STAGE_Y_MAX][STAGE_X_MAX],int origin_map[STAGE_Y_MAX][STAGE_X_MAX],int block[BLOCK_TYPE_MAX])
{
	int i,j;

	for(i = 0; i < BLOCK_TYPE_MAX; i++)
	{
		if(block[i] != 0)
		{
			return FALSE;
		}
	}

	for(i = 0; i < STAGE_Y_MAX; i++)
	{
		for(j = 0; j < STAGE_X_MAX; j++)
		{
			//1�ł����܂��ĂȂ��ꏊ����������I��
			if((map[i][j] & origin_map[i][j]) != origin_map[i][j] )
			{
				//printf("y=%d x=%d map[y][x]= %d origin_map[i][j] = %d\n",i,j,map[i][j],origin_map[i][j]);
				return FALSE;
			}
		}
		//printf("\n");
	}



	return TRUE;

}