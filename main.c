#include<stdio.h>
#define Y_MAX 10
#define X_MAX 10
#define N_BLOCK 4
#define HAICHI_TYPE 12
#define FALSE 0
#define TRUE 1

int mapping(int block[N_BLOCK], int orgin_map[Y_MAX][X_MAX]);
int hantei(int map[Y_MAX][X_MAX] ,int y, int x, int type , int num );
int assign(int map[Y_MAX][X_MAX] ,int y, int x, int type , int num);
int allset(int map[Y_MAX][X_MAX],int y,int x,int t,int origin_map[Y_MAX][X_MAX]);
int G1;
int main (void){
	
	int origin_map[Y_MAX][X_MAX]=
	{
		/*
		{1,1,3,0,0,0,0,0,0,0},
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
	};
	int origin_block[N_BLOCK]={1,1,1,1};
	int i,j;
	G1 = 0;
	

	for(i = 0; i < N_BLOCK; i++)
	{
		printf("%d ",origin_block[i]);
	}
	printf("\n");

	for(i = 0; i < Y_MAX; i++)
	{
		for(j = 0; j < X_MAX; j++)
		{
			printf("%d ",origin_map[i][j]);
		}
		printf("\n");

	}
	printf("\n");

	//処理開始
	 mapping(origin_block, origin_map);



	//結果表示
	for(i = 0; i < Y_MAX; i++)
	{
		for(j = 0; j < X_MAX; j++)
		{
			printf("%d ",origin_map[i][j]);
		}
		printf("\n");

	}
	printf("\n");
	printf("finish\n");

	return 0;
}


int mapping(int block[N_BLOCK], int origin_map[Y_MAX][X_MAX])
{
	int result_map[Y_MAX][X_MAX]={0};
	int y = 2;
	int x = 2;
	int type;
	int num = 2;

	for(y = 0; y < Y_MAX; y++)
	{
		for(x = 0; x < X_MAX; x++)
		{
			result_map[y][x] = origin_map[y][x];
		}
	}
	/*
	for(type = 0; type < HAICHI_TYPE; type++)
	{
		printf("type = %d ::",type);
		if(hantei(origin_map,y,x,type,num)){
			printf("mapping可能\n");
		}
		else
		{
			printf("mapping不可能\n");
		}
	}
	*/

	allset( origin_map,0,0,0,origin_map);



	for(y = 0; y < Y_MAX; y++)
	{
		for(x = 0; x < X_MAX; x++)
		{
			//origin_map[y][x] = result_map[y][x];
		}
	}

	for(y = 0; y < Y_MAX; y++)
	{
		for(x = 0; x < X_MAX; x++)
		{
			printf("%d ", origin_map[y][x]);
		}
		printf("\n");
	}
	printf("\n");

	return TRUE;
}

//配置可能か判定する関数
int hantei(int map[Y_MAX][X_MAX] ,int y, int x, int type , int num )
{
	int block1y,block1x;
	int block2y,block2x;
	int i,j;
	int bufy,bufx;
	if(type > 12 || type < 0)
	{
		return FALSE;
	}

	if(y >= Y_MAX || y < 0)
	{
		return FALSE;
	}
	if(x >= X_MAX || x < 0)
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
			//   ○2
			//
			block1y = y -1;
			block1x = x;
			block2y = y;
			block2x = x + 1;
			if(block1y < 0 || block1x < 0 || block1y >= Y_MAX || block1x >= X_MAX || block2y < 0 || block2x < 0 || block2y >= Y_MAX || block2x >= X_MAX )
			{
				return FALSE;
			}
			
			break;
		case 1:
			//   
			//   ○1
			//   2
			block1y = y;
			block1x = x + 1;
			block2y = y + 1;
			block2x = x;
			if(block1y < 0 || block1x < 0 || block1y >= Y_MAX || block1x >= X_MAX || block2y < 0 || block2x < 0 || block2y >= Y_MAX || block2x >= X_MAX )
			{
				return FALSE;
			}
			
			break;
		case 2:
			//   
			//  2○
			//   1
			block1y = y + 1;
			block1x = x;
			block2y = y;
			block2x = x - 1;
			if(block1y < 0 || block1x < 0 || block1y >= Y_MAX || block1x >= X_MAX || block2y < 0 || block2x < 0 || block2y >= Y_MAX || block2x >= X_MAX )
			{
				return FALSE;
			}
			
			break;
		case 3:
			//   1
			//  2○
			//   
			block1y = y - 1;
			block1x = x;
			block2y = y;
			block2x = x - 1;
			if(block1y < 0 || block1x < 0 || block1y >= Y_MAX || block1x >= X_MAX || block2y < 0 || block2x < 0 || block2y >= Y_MAX || block2x >= X_MAX )
			{
				return FALSE;
			}
			
			break;
		case 4:
			//   
			//   ○
			//   1  2
			block1y = y + 1;
			block1x = x ;
			block2y = y + 1;
			block2x = x + 1;
			if(block1y < 0 || block1x < 0 || block1y >= Y_MAX || block1x >= X_MAX || block2y < 0 || block2x < 0 || block2y >= Y_MAX || block2x >= X_MAX )
			{
				return FALSE;
			}
			
			break;
		case 5:
			//   
			// 1 ○
			// 2    
			block1y = y;
			block1x = x - 1;
			block2y = y + 1;
			block2x = x - 1;
			if(block1y < 0 || block1x < 0 || block1y >= Y_MAX || block1x >= X_MAX || block2y < 0 || block2x < 0 || block2y >= Y_MAX || block2x >= X_MAX )
			{
				return FALSE;
			}
			
			break;
		case 6:
			// 2 1
			//   ○
			//   
			block1y = y - 1;
			block1x = x;
			block2y = y - 1;
			block2x = x - 1;
			if(block1y < 0 || block1x < 0 || block1y >= Y_MAX || block1x >= X_MAX || block2y < 0 || block2x < 0 || block2y >= Y_MAX || block2x >= X_MAX )
			{
				return FALSE;
			}
			
			break;
		case 7:
			//     2
			//   ○1
			//   
			block1y = y;
			block1x = x + 1;
			block2y = y - 1;
			block2x = x + 1;
			if(block1y < 0 || block1x < 0 || block1y >= Y_MAX || block1x >= X_MAX || block2y < 0 || block2x < 0 || block2y >= Y_MAX || block2x >= X_MAX )
			{
				return FALSE;
			}
			
			break;
		case 8:
			//   
			//   ○
			// 2 1  
			block1y = y + 1;
			block1x = x;
			block2y = y + 1;
			block2x = x - 1;
			if(block1y < 0 || block1x < 0 || block1y >= Y_MAX || block1x >= X_MAX || block2y < 0 || block2x < 0 || block2y >= Y_MAX || block2x >= X_MAX )
			{
				return FALSE;
			}
			
			break;
		case 9:
			//   
			//   ○1
			//     2
			block1y = y;
			block1x = x + 1;
			block2y = y + 1;
			block2x = x + 1;
			if(block1y < 0 || block1x < 0 || block1y >= Y_MAX || block1x >= X_MAX || block2y < 0 || block2x < 0 || block2y >= Y_MAX || block2x >= X_MAX )
			{
				return FALSE;
			}
			
			break;
		case 10:
			//   1 2
			//   ○
			//     
			block1y = y - 1;
			block1x = x;
			block2y = y - 1;
			block2x = x + 1;
			if(block1y < 0 || block1x < 0 || block1y >= Y_MAX || block1x >= X_MAX || block2y < 0 || block2x < 0 || block2y >= Y_MAX || block2x >= X_MAX )
			{
				return FALSE;
			}
			
			break;
		case 11:
			// 2  
			// 1 ○
			//     
			block1y = y;
			block1x = x - 1;
			block2y = y - 1;
			block2x = x - 1;
			if(block1y < 0 || block1x < 0 || block1y >= Y_MAX || block1x >= X_MAX || block2y < 0 || block2x < 0 || block2y >= Y_MAX || block2x >= X_MAX )
			{
				return FALSE;
			}
		
			break;
		default:
				return FALSE;
			break;

		}
		//チェック対象ブロックが配置可能か判定
		if((map[block1y][block1x] == 0 || map[block1y][block1x] == num) && (map[block2y][block2x] == 0 || map[block2y][block2x] == num) ){
		}
		else
		{
			return FALSE;
		}


		
		//チェック対象のブロックに隣接するブロックに同一ナンバーがないか確認
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
			if(bufx+1 < X_MAX)
			{
				if(map[bufy][bufx+1] == num)
				{
					//printf("2 ");
					if(!((bufy == y && bufx+1 == x) || (bufy == block1y && bufx + 1 == block1x) || (bufy == block2y && bufx + 1 == block2x)) ){
						return FALSE;
					}
				}
			}

			if(bufy+1 < Y_MAX)
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

int assign(int map[Y_MAX][X_MAX] ,int y, int x, int type , int num)
{
	int block1y,block1x,block2y,block2x;

	switch (type)
		{
		case 0:
			//   1
			//   ○2
			//
			block1y = y -1;
			block1x = x;
			block2y = y;
			block2x = x + 1;
		
			
			break;
		case 1:
			//   
			//   ○1
			//   2
			block1y = y;
			block1x = x + 1;
			block2y = y + 1;
			block2x = x;
			
			
			break;
		case 2:
			//   
			//  2○
			//   1
			block1y = y + 1;
			block1x = x;
			block2y = y;
			block2x = x - 1;
			
			
			break;
		case 3:
			//   1
			//  2○
			//   
			block1y = y - 1;
			block1x = x;
			block2y = y;
			block2x = x - 1;
			
			
			break;
		case 4:
			//   
			//   ○
			//   1  2
			block1y = y + 1;
			block1x = x ;
			block2y = y + 1;
			block2x = x + 1;
			
			
			break;
		case 5:
			//   
			// 1 ○
			// 2    
			block1y = y;
			block1x = x - 1;
			block2y = y + 1;
			block2x = x - 1;
			
			
			break;
		case 6:
			// 2 1
			//   ○
			//   
			block1y = y - 1;
			block1x = x;
			block2y = y - 1;
			block2x = x - 1;
			
			
			break;
		case 7:
			//     2
			//   ○1
			//   
			block1y = y;
			block1x = x + 1;
			block2y = y - 1;
			block2x = x + 1;
			
			
			break;
		case 8:
			//   
			//   ○
			// 2 1  
			block1y = y + 1;
			block1x = x;
			block2y = y + 1;
			block2x = x - 1;
			
			
			break;
		case 9:
			//   
			//   ○1
			//     2
			block1y = y;
			block1x = x + 1;
			block2y = y + 1;
			block2x = x + 1;
			
			
			break;
		case 10:
			//   1 2
			//   ○
			//     
			block1y = y - 1;
			block1x = x;
			block2y = y - 1;
			block2x = x + 1;
			
			break;
		case 11:
			// 2  
			// 1 ○
			//     
			block1y = y;
			block1x = x - 1;
			block2y = y - 1;
			block2x = x - 1;
			
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
//制約ブロック配置関数
int allset(int map[Y_MAX][X_MAX],int y,int x,int t,int origin_map[Y_MAX][X_MAX])
{
	int i,j;
	int posY,posX,type;
	int bufx=0;

	int sub_map[Y_MAX][X_MAX]={0};
	
	//転写
	for(i = 0; i < Y_MAX; i++)
	{
		for(j = 0; j < X_MAX; j++)
		{
			sub_map[i][j] = map[i][j];
		}
	}
	G1++;
	bufx = x;
	for(posY = y; posY < Y_MAX; posY++)
	{
		for(posX = bufx; posX < X_MAX; posX++)
		{
			//オリジナルの座標だけを対象にする
			if(origin_map[posY][posX] != 0)
			{
				
				for(type = t; type < HAICHI_TYPE; type++)
				{
					if(hantei(sub_map,posY,posX,type,sub_map[posY][posX]))
					{
						
						//割当て
						assign(sub_map,posY,posX,type,sub_map[posY][posX]);
						//printf("allset\n");
						if(FALSE == allset(sub_map,posY,posX + 1,0,origin_map))
						{
							//失敗時マップ復元
							for(i = 0; i < Y_MAX; i++)
							{
								for(j = 0; j < X_MAX; j++)
								{
									sub_map[i][j] = map[i][j];
								}
							}
						}
						else
						{
							//成功時
							for(i = 0; i < Y_MAX; i++)
							{
								for(j = 0; j < X_MAX; j++)
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
					for(i = 0; i < Y_MAX; i++)
					{
						for(j = 0; j < X_MAX; j++)
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
	for(i = 0; i < Y_MAX; i++)
	{
		for(j = 0; j < X_MAX; j++)
		{
			printf("%d ",map[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	*/
	//変更後マップ反映
	

	return TRUE;
}

//評価関数


//非制約ブロック配置関数