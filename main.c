
#define STAGE_Y_MAX 9
#define STAGE_X_MAX 9
#define Q3_ANS_MAX 20

typedef struct {
	int sx;
	int sy;
	int ex;
	int ey;
}ANS_TAG;

typedef struct {
	int m_isPair;
	ANS_TAG m_ansPtr[2];
	int m_score;
	int m_kaburi[40];//1000個格納できれば十分 0で初期化
	int m_saiyo; //2 被りなしでは採用しない, 1 ?, 0 NO
	int m_color;
}SCORE;

typedef struct {
	SCORE m_score[2000];
	int order[2000];
	int count;
}SCORE_LIST;

typedef struct
{
	int m_score[1024];//適当2^16 正しい範囲はあとで探る
	int m_startPos;
	int m_endPos;
}OPTTABLE;
//saiyo = 0はどうする？ぬかすか

typedef struct
{
	OPTTABLE optTable[62];//75個あればいけると思う//二けたは使わないからもっと減らせる　3桁以上62 4桁以上54 5桁以上10
	int tranList[2000];
	int count;

}OPTTABLELIST;

typedef struct
{
	int ansIndex[Q3_ANS_MAX];
	int nAnsIndex;  //ペアを考慮していない数
	int nAns;		//ペアを考慮した数_Ansの方
	int score;
	int anaStartPos;
}ANSWER;

#define ANSLISTSIZE 1000

typedef struct
{
	ANSWER list[ANSLISTSIZE];
	int min;
	int count;
	int size;
}ANSWERLIST;

typedef struct
{
	int *score;
	int element[32];
	int adjacent[32];
	int size;
	int maxScore;
}BLOCK;

typedef struct
{
	BLOCK *block;
	int size;
}BLOCK_LIST;

int BITMASK[32] =
{
	0x00000001,
	0x00000002,
	0x00000004,
	0x00000008,
	0x00000010,
	0x00000020,
	0x00000040,
	0x00000080,
	0x00000100,
	0x00000200,
	0x00000400,
	0x00000800,
	0x00001000,
	0x00002000,
	0x00004000,
	0x00008000,
	0x00010000,
	0x00020000,
	0x00040000,
	0x00080000,
	0x00100000,
	0x00200000,
	0x00400000,
	0x00800000,
	0x01000000,
	0x02000000,
	0x04000000,
	0x08000000,
	0x10000000,
	0x20000000,
	0x40000000,
	0x80000000,
};


ANSWERLIST AnswerList;


#define TRUE 1
#define FALSE 0
#define BOOL int



int prog_q2(int para);
void Set1Bit(int* arr, int index);
void Set0Bit(int* arr, int index);
BOOL GetScoreList2(const int stage[STAGE_Y_MAX][STAGE_X_MAX], SCORE_LIST* ScoreList);
int GetNumber3(const int stage[STAGE_Y_MAX][STAGE_X_MAX], int startx, int starty, int endx, int endy);
BOOL GetEndPos(int startx, int starty, int length, int dir, int *endx, int *endy);
int IsPointOnSegment(int x, int y, int x1, int y1, int x2,int y2);
int GetKeta(int num);
int cmp(const void *p, const void *q);
int prog_q3(const int stage[STAGE_Y_MAX][STAGE_X_MAX], ANS_TAG Ans[Q3_ANS_MAX]);
BOOL IsIntersected(int sx1, int sy1, int ex1, int ey1, int sx2, int sy2, int ex2, int ey2 );
int GetPoint3(const int stage[STAGE_Y_MAX][STAGE_X_MAX], SCORE_LIST *ScoreList,int ansIndex[Q3_ANS_MAX],int nAns);
BOOL Is1Bit(int* arr, int index);
int GetYousosu2(  ANSWER* Answer, SCORE_LIST* ScoreList);
BOOL Saiki11(const int stage[STAGE_Y_MAX][STAGE_X_MAX], ANSWER* Answer, SCORE_LIST* ScoreList,int startPos, int endPos);
int EasyGetPoint(SCORE_LIST *ScoreList,int ansIndex[Q3_ANS_MAX],int nAnsIndex);
BOOL Coloring(SCORE_LIST* ScoreList, int* nColor);
BOOL StaticAnalisys(SCORE_LIST* ScoreList);
int MakeBlockList(SCORE_LIST* ScoreList, int nColor, BLOCK_LIST* blockList);
int main(void)
{
	int **stage;
	int i,j,n;
	 ANS_TAG Ans[Q3_ANS_MAX];
	for( n = 0; n < 2 ; n++)
	{
		stage = (int**)stageList[n];

		for ( i = 0; i < 9; i++)
		{
			for ( j = 0; j < 9; j++)
			{
				printf(" %d",*(stage+i*9+j));
			}
			printf("\n");
		}
		printf("\n\n");

		prog_q3((int**)stage, Ans);

	}

	return 0;
}
//被っていたらbitが立つ

BOOL Coloring(SCORE_LIST* ScoreList, int* nColor)
{
	int i,j,nowColor,count,buf;
	nowColor = 1;

	for (i=0;i<ScoreList->count;i++)
	{
		if (ScoreList->m_score[i].m_color == 0&& ScoreList->m_score[i].m_saiyo == 1)
		{
			ScoreList->m_score[i].m_color = nowColor;
			count = 1;
			for ( j =0;j<ScoreList->count;j++)
			{
				if( !Is1Bit(ScoreList->m_score[i].m_kaburi,j)&&ScoreList->m_score[j].m_color == 0&&ScoreList->m_score[j].m_saiyo == 1&& i!= j)
				{
					ScoreList->m_score[j].m_color = nowColor;
					count++;
					if(count >= 15)break;
				}
			}
			nowColor++;
		}
	}
	buf=0;
	for ( i=0;i<ScoreList->count;i++)
	{
		if (buf<ScoreList->m_score[i].m_color)
		{
			buf=ScoreList->m_score[i].m_color;
		}
	}
	if ( i==ScoreList->count)*nColor=buf-1;
	return TRUE;
}

BOOL StaticAnalisys(SCORE_LIST* ScoreList)
{
	int i,j,ketaCount,buf=0,flag=0;
	ANSWER ans;
	ans.nAns = 0;
	ans.nAnsIndex =0;

	for (j=0;j<ScoreList->count;j++)
	{
		if (ScoreList->m_score[j].m_saiyo != 0)
		{
			buf =0;
			ketaCount = STAGE_Y_MAX*STAGE_X_MAX;
			for( i= 0; i<=j;i++)
			{
				if (ScoreList->m_score[i].m_score != 0)
				{
					ketaCount -= GetKeta(ScoreList->m_score[i].m_score);
				}
				if (ketaCount <= 0)
				{
					break;
				}
			}

			for (i=j+1;i<ScoreList->count;i++)
			{
				buf += ScoreList->m_score[i].m_score;
				ketaCount -= GetKeta(ScoreList->m_score[i].m_score);
				if(ketaCount <= 0)
				{
					break;
				}
			}
			if ( buf<= ScoreList->m_score[j].m_score)
			{
				ans.ansIndex[ans.nAnsIndex]=j;
				ans.nAnsIndex++;
				ans.nAns = ScoreList->m_score[j].m_isPair + 1;
				if ( ans.nAns + GetYousosu2( &ans,ScoreList) >= Q3_ANS_MAX)
				{
					flag = 1;
					ScoreList->m_score[j].m_saiyo = 2;
					for (i=j+1; i <ScoreList->count;i++)
					{
						if (!Is1Bit(ScoreList->m_score[j].m_kaburi,i))
						{
							ScoreList->m_score[i].m_saiyo = 0;
						}
					}
					if (ans.nAns + GetYousosu2(&ans,ScoreList) <= 25)return TRUE;
				}
				else
				{
					ans.nAnsIndex--;
					ans.nAns -= (ScoreList->m_score[j].m_isPair + 1);
				}
				
			}
			else
			{
				if (flag==1)return TRUE;
				return FALSE;
			}
		}
	}
	if(flag == 1)return TRUE;
	return FALSE;
}

BOOL PushEasyAnsList( const int stage[STAGE_Y_MAX][STAGE_X_MAX], ANSWER* Answer, SCORE_LIST* ScoreList )
{
	int i,j,point,w1 = INT_MAX,w2 = INT_MAX,w1pos;
	
	point = EasyGetPoint(ScoreList,Answer->ansIndex,Answer->nAnsIndex);

	//同じ要素
	for (i =0; i<AnswerList.count; i++)
	{
		if (AnswerList.list[i].score == point)
		{
			for (j=0;j<AnswerList.list[i].nAnsIndex;j++)
			{
				if (AnswerList.list[i].ansIndex[j]!=Answer->ansIndex[j])
				{
					break;
				}
			}
			if (j==AnswerList.list[i].nAnsIndex)
			{
				return FALSE;
			}
		}
	}

	//空いてるなら入れる
	if( AnswerList.count < AnswerList.size)
	{
		AnswerList.list[AnswerList.count] = *(Answer);
		AnswerList.list[AnswerList.count].score = point;
		if( AnswerList.min > point )
		{
			AnswerList.min = point;
		}
		AnswerList.count++;
	}
	else//空いていない
	{
		if( AnswerList.min < point )
		{
			//minの次の最小を探す
			for( i = 0; i < AnswerList.count; i++)
			{
				if( w1 > EasyGetPoint(ScoreList,AnswerList.list[i].ansIndex,AnswerList.list[i].nAnsIndex))
				{
					w2 = w1;
					w1 = EasyGetPoint(ScoreList,AnswerList.list[i].ansIndex,AnswerList.list[i].nAnsIndex);
					w1pos = i;
				}
				else if(w2 > EasyGetPoint(ScoreList,AnswerList.list[i].ansIndex,AnswerList.list[i].nAnsIndex))
				{
					w2 = EasyGetPoint(ScoreList,AnswerList.list[i].ansIndex,AnswerList.list[i].nAnsIndex);
				}

			}
			//min更新
			AnswerList.list[w1pos] = *Answer;
			AnswerList.list[w1pos].score = point;
			AnswerList.min = w2;
		}
		else
		{
			return FALSE;
		}
	}
	return TRUE;
}

BOOL Saiki11(const int stage[STAGE_Y_MAX][STAGE_X_MAX], ANSWER* Answer, SCORE_LIST* ScoreList,int startPos, int endPos)
{
	int i,j;
	int nAns,nAnsIndex;

	if( Answer->nAns +  GetYousosu2( Answer, ScoreList) < Q3_ANS_MAX)
	{
		return FALSE;
	}

	if( startPos > endPos)
	{
		return FALSE;
	}

	if( Answer->nAns > Q3_ANS_MAX )
	{
		return FALSE;
	}

	//BlockListによる判定
	//ブロックごとスキップするなら戻り値で判定

	//Score
	//記録
	PushEasyAnsList(stage, Answer, ScoreList );

	if(ScoreList->m_score[ScoreList->order[startPos]].m_saiyo == 0)
	{
		return Saiki11(stage, Answer, ScoreList,startPos+1,endPos);
	}
	else if(ScoreList->m_score[ScoreList->order[startPos]].m_saiyo == 2)//引っかからない
	{
		Answer->ansIndex[Answer->nAnsIndex] = ScoreList->order[startPos];
		Answer->nAnsIndex++;
		Answer->nAns += ScoreList->m_score[ScoreList->order[startPos]].m_isPair + 1;
		return Saiki11(stage, Answer, ScoreList,startPos+1,endPos);
	}

	//重なりがないか確認
	for( i = 0; i < Answer->nAnsIndex; i++)
	{
		if (!Is1Bit(ScoreList->m_score[ScoreList->order[startPos]].m_kaburi, Answer->ansIndex[i]))
		{
			break;
		}
	}
	if( i !=  Answer->nAnsIndex )//被りあり
	{
		return Saiki11(stage, Answer, ScoreList,startPos+1,endPos);
	}

	//採用
	nAns = Answer->nAns;
	nAnsIndex = Answer->nAnsIndex;
	Answer->ansIndex[Answer->nAnsIndex] = ScoreList->order[startPos];
	Answer->nAnsIndex++;
	Answer->nAns += ScoreList->m_score[ScoreList->order[startPos]].m_isPair + 1;
	if (Saiki11(stage, Answer, ScoreList,startPos+1,endPos))
	{
		return TRUE;
	}
	Answer->nAns = nAns;
	Answer->nAnsIndex = nAnsIndex;


	//非採用
	return Saiki11(stage, Answer, ScoreList,startPos+1,endPos);
}

int BlockCheck( SCORE_LIST* ScoreList, BLOCK_LIST* blockList, ANSWER* Answer, int blockStartPos )
{
	int ansScore,upper,i,j,buf,blockPos;

	ansScore = EasyGetPoint(ScoreList,Answer->ansIndex, Answer->nAnsIndex);

	buf =0;
	for ( i=0; i <blockList->size; i++)
	{
		if(blockStartPos - blockList->block[i].size < 0)
		{
			break;
		}
		else
		{
			blockStartPos -= blockList->block[i].size;
		}
	}
	blockPos = i;

	upper = 0;//今のブロックの値

	for (i= blockPos+1; i < blockList->size; i++)//対象ブロックまで最大値の合計
	{
		//被ってなくて最大値のブロック
		//upper += blockList->block[i].maxScore;
	}

	if (upper > ansScore)return 0;
	return 1;
}

int GetYousosu2(  ANSWER* Answer, SCORE_LIST* ScoreList)
{
	int i,j,count = 0;
	for( i = 0; i < ScoreList->count; i++)
	{
		if (ScoreList->m_score[i].m_isPair == 0)
		{
			for( j = 0; j < Answer->nAnsIndex; j++)
			{
				if(!Is1Bit(ScoreList->m_score[i].m_kaburi,Answer->ansIndex[j]) || i == Answer->ansIndex[j])
				{
					break;//被り
				}
			}
			if( j == Answer->nAnsIndex)
			{
				count++;
			}
		}
	}
	return count;
}

int MakeBlockList(SCORE_LIST* ScoreList, int nColor, BLOCK_LIST* blockList)
{
	int i,j,k,buf,buf2,bj,bj1,v,set,unused,used;
	blockList->size = nColor;
	blockList->block = (BLOCK*)malloc(sizeof(BLOCK)*nColor);
	if(blockList->block==NULL)printf("ERROR\n");

	for (i=0;i<nColor;i++)
	{
		buf = 0;
		for (j=0; j <ScoreList->count;j++)
		{
			buf2=0;
			if (ScoreList->m_score[j].m_color == i+1)
			{
				blockList->block[i].element[buf]=j;
				blockList->block[i].adjacent[buf]=0;
				for (k=0; k<ScoreList->count;k++)
				{
					if (Is1Bit(ScoreList->m_score[j].m_kaburi,k) && ScoreList->m_score[k].m_color ==(i+1))
					{
						Set1Bit(&blockList->block[i].adjacent[buf],buf2);
					}

					if (ScoreList->m_score[k].m_color == (i+1))buf2++;
				}
				buf++;
			}
		}
		blockList->block[i].size = buf;
		blockList->block[i].score = (int*)malloc(sizeof(int)*(1<<blockList->block[i].size));
		if(blockList->block[i].score==NULL)printf("ERROR\n");
	}

	for ( i=0;i<nColor;i++)
	{
		blockList->block[i].score[0] = 0;
		for (j=0;j<blockList->block[i].size;j++)
		{
			bj = 1<< j;
			bj1 = 1 << (j+1);
			v = j;
			for (set =bj;set<bj1;set++)
			{
				unused = blockList->block[i].score[set-bj];
				used = blockList->block[i].score[blockList->block[i].adjacent[v] & set] + ScoreList->m_score[blockList->block[i].element[v]].m_score;
				if (used>unused)
				{
					blockList->block[i].score[set]=used;
				}
				else
				{
					blockList->block[i].score[set] =unused;
				}
				printf("b[%d][%d]=%d\n",i,set,blockList->block[i].score[set]);
			}
		}
	}
	return TRUE;
}

BOOL InitialOptTableList(const int stage[STAGE_Y_MAX][STAGE_X_MAX], SCORE_LIST* ScoreList,OPTTABLELIST* optTableList)
{
	int i,j;
	optTableList->count = 0;
	for(j = 0, i = 0; i < ScoreList->count; i++)
	{
		//彩色初期化
		ScoreList->m_score[i].m_color = 0;
		
		//
		if(ScoreList->m_score[i].m_saiyo >= 1)
		{
			optTableList->tranList[j] = i;
			optTableList->count++;
		}
	}

	//彩色割り当て……あとで色々試してみる
	//被りまくっている奴同士をまとめた方が効率的
	//上位スコアのやつらはまとめておく……斜めのやつとか考慮した方がいい…端っこのやつは別にしていた方がいい
	ScoreList->m_score[0].m_color = 1;
	for(i = 0; i < 15; i++)
	{
		ScoreList->m_score[i].m_color = 1;
	}



	for( j = 1; optTableList->optTable[j].m_endPos < optTableList->count; j++ )
	{
		//再帰する
	}

	return TRUE;
}

//BOOL saiki10( SCORE_LIST* ScoreList, ANSWER ans, TargetList targetList,int* result)
//{
//	int i,j;
//
//	//必ず採用とかぶりがないか?
//	
//	//既存のAnsとかぶりはないか?
//
//	//被りがあったら飛ばす
//	
//}

//もしかしたらこっちの方が早いかもしれない
int GetNumber3(const int stage[STAGE_Y_MAX][STAGE_X_MAX], int startx, int starty, int endx, int endy)
{
	int result = 0;
	int x,y;
	x = startx;
	y = starty;

	if ( startx < endx && starty == endy )//0
	{
		while(x <= endx)
		{
			result = result * 10;
			result += stage[y][x];
			x++;
		}
	}
	else if ( startx == endx && starty < endy )//1
	{
		while( y <= endy)
		{
			result = result * 10;
			result += stage[y][x];
			y++;
		}
	}
	else if ( startx > endx && starty == endy )//2
	{
		while( x >= endx)
		{
			result = result * 10;
			result += stage[y][x];
			x--;
		}
	}
	else if ( startx == endx && starty > endy )//3
	{
		while( y >= endy)
		{
			result = result * 10;
			result += stage[y][x];
			y--;
		}
	}
	else if ( startx < endx && starty < endy )//4
	{
		while( y <= endy)
		{
			result = result * 10;
			result += stage[y][x];
			y++;
			x++;
		}
	}
	else if ( startx > endx && starty < endy )//5
	{
		while( y <= endy)
		{
			result = result * 10;
			result += stage[y][x];
			y++;
			x--;
		}
	}
	else if ( startx > endx && starty > endy )//6
	{
		while( y >= endy)
		{
			result = result * 10;
			result += stage[y][x];
			y--;
			x--;
		}
	}
	else //7
	{
		while( y >= endy)
		{
			result = result * 10;
			result += stage[y][x];
			y--;
			x++;
		}
	}

	return result;

}
int GetKeta(int num)
{
	int buf,keta = 0;
	buf = num;
	while(buf != 0)
	{
		buf = buf /10;
		keta++;
	}
	return keta;
}

BOOL GetScoreList2(const int stage[STAGE_Y_MAX][STAGE_X_MAX], SCORE_LIST* ScoreList)
{
	int len,x,y,dir,endx,endy, buf;
	int i,j,k;

	//全ての素数を取得
	for (len = 9; len > 1; len--)
	{
		for (x = 0; x < STAGE_X_MAX;x++)
		{
			for (y = 0; y < STAGE_Y_MAX;y++)
			{
				if(stage[y][x] != 0)
				{
					for (dir = 0; dir < 8; dir++)
					{
						GetEndPos(x,y,len,dir,&endx,&endy);
						if(endx <0 || endy < 0 || endy >= STAGE_Y_MAX ||endx >= STAGE_X_MAX )continue;
						buf = GetNumber3(stage,x,y,endx,endy);
						if(prog_q2(buf))
						{
							ScoreList->m_score[ScoreList->count].m_ansPtr[0].sx = x;
							ScoreList->m_score[ScoreList->count].m_ansPtr[0].sy = y;
							ScoreList->m_score[ScoreList->count].m_ansPtr[0].ex = endx;
							ScoreList->m_score[ScoreList->count].m_ansPtr[0].ey = endy;
							ScoreList->m_score[ScoreList->count].m_score = buf;
							ScoreList->m_score[ScoreList->count].m_saiyo = 1;
							ScoreList->m_score[ScoreList->count].m_isPair = 0;
							ScoreList->count++;
							
							//始点と終点が反対の座標がないか
							for( i = 0; i < ScoreList->count-1; i++)
							{
								//Pairじゃない
								if(ScoreList->m_score[i].m_isPair == 0)
								{
									if(ScoreList->m_score[i].m_ansPtr[0].sx == endx && ScoreList->m_score[i].m_ansPtr[0].sy == endy &&ScoreList->m_score[i].m_ansPtr[0].ex == x && ScoreList->m_score[i].m_ansPtr[0].ey == y )
									{
										break;
									}
								}
							}
							if( i  != ScoreList->count-1)
							{
								//小さい方は採用しない 0
								if(ScoreList->m_score[ScoreList->count-1].m_score > ScoreList->m_score[i].m_score)
								{
									ScoreList->m_score[i].m_saiyo = 0;
								}
								else
								{
									ScoreList->m_score[ScoreList->count-1].m_saiyo = 0;
									
								}
							}
						}
					}
				}
			}
		}
	}

	for (j = 0; j < ScoreList->count; j++)
	{
		if(ScoreList->m_score[j].m_isPair == 0)
		{
			x	 = ScoreList->m_score[j].m_ansPtr[0].sx;
			y	 = ScoreList->m_score[j].m_ansPtr[0].sy;
			endx = ScoreList->m_score[j].m_ansPtr[0].ex;
			endy = ScoreList->m_score[j].m_ansPtr[0].ey;
			//同じ値がないか
			for( i = j+1; i < ScoreList->count; i++)
			{
				//対象がPairじゃない
				if(ScoreList->m_score[i].m_isPair == 0)
				{
					if (!IsIntersected(ScoreList->m_score[i].m_ansPtr[0].sx,ScoreList->m_score[i].m_ansPtr[0].sy,ScoreList->m_score[i].m_ansPtr[0].ex,ScoreList->m_score[i].m_ansPtr[0].ey,x,y,endx,endy))
					{
						//値が等しいとき
						if(ScoreList->m_score[j].m_score == ScoreList->m_score[i].m_score )
						{
							//始点と終点の反対座標で採用しない場合でもペアとしては採用するかもしれない
							ScoreList->m_score[ScoreList->count].m_ansPtr[0].sx = x;
							ScoreList->m_score[ScoreList->count].m_ansPtr[0].sy = y;
							ScoreList->m_score[ScoreList->count].m_ansPtr[0].ex = endx;
							ScoreList->m_score[ScoreList->count].m_ansPtr[0].ey = endy;
							ScoreList->m_score[ScoreList->count].m_ansPtr[1].sx = ScoreList->m_score[i].m_ansPtr[0].sx;
							ScoreList->m_score[ScoreList->count].m_ansPtr[1].sy = ScoreList->m_score[i].m_ansPtr[0].sy;
							ScoreList->m_score[ScoreList->count].m_ansPtr[1].ex = ScoreList->m_score[i].m_ansPtr[0].ex;
							ScoreList->m_score[ScoreList->count].m_ansPtr[1].ey = ScoreList->m_score[i].m_ansPtr[0].ey;
							ScoreList->m_score[ScoreList->count].m_score = ScoreList->m_score[i].m_score;
							for(k=0; k < GetKeta(ScoreList->m_score[i].m_score); k++)
							{
								ScoreList->m_score[ScoreList->count].m_score *= 10;
							}
							ScoreList->m_score[ScoreList->count].m_score += ScoreList->m_score[i].m_score;
							ScoreList->m_score[ScoreList->count].m_saiyo = 1;
							ScoreList->m_score[ScoreList->count].m_isPair = 1;
							ScoreList->count++;
						}
					}
				}
			}
		}
	}


	//SORT
	qsort((void*)&ScoreList->m_score[0], ScoreList->count, sizeof(SCORE),cmp);
	for( i = 0; i < 35; i++ )
	{
		printf("%d %d %d %d\n ",i,ScoreList->m_score[i].m_score,ScoreList->m_score[i].m_isPair,ScoreList->m_score[i].m_saiyo);
	}
	//被りリスト作成
	for (i = 0; i < ScoreList->count; i++)
	{
		for (j = 0;j<40;j++)
		{
			ScoreList->m_score[i].m_kaburi[j] = ~0;
		}
		for ( j = 0; j < ScoreList->count; j++)
		{
			if( i== j) Set0Bit(ScoreList->m_score[i].m_kaburi,j);
			if ( i != j)
			{
				if (IsIntersected(ScoreList->m_score[i].m_ansPtr[0].sx,ScoreList->m_score[i].m_ansPtr[0].sy,ScoreList->m_score[i].m_ansPtr[0].ex,ScoreList->m_score[i].m_ansPtr[0].ey,ScoreList->m_score[j].m_ansPtr[0].sx,ScoreList->m_score[j].m_ansPtr[0].sy,ScoreList->m_score[j].m_ansPtr[0].ex,ScoreList->m_score[j].m_ansPtr[0].ey))
				{
					Set0Bit(ScoreList->m_score[i].m_kaburi,j);
					continue;
				}
				if (ScoreList->m_score[i].m_isPair == 1)
				{
					if (IsIntersected(ScoreList->m_score[i].m_ansPtr[1].sx,ScoreList->m_score[i].m_ansPtr[1].sy,ScoreList->m_score[i].m_ansPtr[1].ex,ScoreList->m_score[i].m_ansPtr[1].ey, ScoreList->m_score[j].m_ansPtr[0].sx,ScoreList->m_score[j].m_ansPtr[0].sy,ScoreList->m_score[j].m_ansPtr[0].ex,ScoreList->m_score[j].m_ansPtr[0].ey))
					{
						Set0Bit(ScoreList->m_score[i].m_kaburi,j);
						continue;
					}
				}
				if (ScoreList->m_score[j].m_isPair == 1)
				{
					if (IsIntersected(ScoreList->m_score[i].m_ansPtr[0].sx,ScoreList->m_score[i].m_ansPtr[0].sy,ScoreList->m_score[i].m_ansPtr[0].ex,ScoreList->m_score[i].m_ansPtr[0].ey,ScoreList->m_score[j].m_ansPtr[1].sx,ScoreList->m_score[j].m_ansPtr[1].sy,ScoreList->m_score[j].m_ansPtr[1].ex,ScoreList->m_score[j].m_ansPtr[1].ey))
					{
						Set0Bit(ScoreList->m_score[i].m_kaburi,j);
						continue;
					}
				}
				if (ScoreList->m_score[i].m_isPair == 1 && ScoreList->m_score[j].m_isPair == 1)
				{
					if (IsIntersected(ScoreList->m_score[i].m_ansPtr[1].sx,ScoreList->m_score[i].m_ansPtr[1].sy,ScoreList->m_score[i].m_ansPtr[1].ex,ScoreList->m_score[i].m_ansPtr[1].ey,ScoreList->m_score[j].m_ansPtr[1].sx,ScoreList->m_score[j].m_ansPtr[1].sy,ScoreList->m_score[j].m_ansPtr[1].ex,ScoreList->m_score[j].m_ansPtr[1].ey))
					{
						Set0Bit(ScoreList->m_score[i].m_kaburi,j);
						continue;
					}
				}
			}
		}
	}

	for (i = 0; i < ScoreList->count;i++)
	{
		if (Is1Bit(ScoreList->m_score[0].m_kaburi,i))
		{
			printf("1 ");
		}
		else
		{
			printf("0 ");
		}
		if(i % 10 == 0)
		printf("\n%d  ",i);
	}
	return TRUE;
}

int cmp(const void *p, const void *q)
{
	return ((SCORE*)q)->m_score -((SCORE*)p)->m_score ;
}

int cmp2(const void *p, const void *q)
{
	return ((ANSWER*)q)->score -((ANSWER*)p)->score ;
}

BOOL GetEndPos(int startx, int starty, int length, int dir, int *endx, int *endy)
{
	switch(dir)
	{
	case 0:
		*endx = startx + length -1;
		*endy = starty;
		break;
	case 1:
		*endx = startx;
		*endy = starty + length - 1;
		break;
	case 2:
		*endx = startx - length + 1;
		*endy = starty;
		break;
	case 3:
		*endx = startx;
		*endy = starty - length + 1;
		break;
	case 4:
		*endx = startx + length - 1;
		*endy = starty + length - 1;
		break;
	case 5:
		*endx = startx - length + 1;
		*endy = starty + length - 1;
		break;
	case 6:
		*endx = startx - length + 1;
		*endy = starty - length + 1;
		break;
	case 7:
		*endx = startx + length - 1;
		*endy = starty - length + 1;
		break;
	}
	return TRUE;
}
int IsPointOnSegment(int x, int y, int x1, int y1, int x2, int y2)
{
	int d;
	if (x1 > x2)
	{
		d = x1, x1 = x2 , x2 = d;
		d = y1, y1 = y2 , y2 = d;
	}
	return x1 <= x && x <= x2 && ((y1 <= y2 && y1 <= y && y <= y2) || (y1 > y2 && y2 <= y && y <= y1)) && (y-y1)*(x2 -x1) == (y2 -y1)*(x-x1);
}
//GetScoreListしか使わない予定……多少遅くても大丈夫
BOOL IsIntersected(int sx1, int sy1, int ex1, int ey1, int sx2, int sy2, int ex2, int ey2 )
{
	int k,j;
	if( sx1 == sx2 &&  sy1 == sy2 || sx1 == ex2 && sy1 == ey2 || ex1 == sx2 && ey1 == sy2 || ex1 == ex2 && ey1 == ey2)
	{
		return TRUE;
	}

	if(sx1 < ex1 && sy1 == ey1)//0
	{
		for ( j = sx1;j <= ex1; j++)
		{
			if(IsPointOnSegment(j,sy1,sx2,sy2,ex2,ey2))return TRUE;
		}
	}
	else if(sx1 == ex1 && sy1 < ey1)//1
	{
		for ( j = sy1;j <= ey1; j++)
		{
			if(IsPointOnSegment(sx1,j,sx2,sy2,ex2,ey2))return TRUE;
		}
	}
	else if(sx1 > ex1 && sy1 == ey1)//2
	{
		for ( j = sx1;j >= ex1; j--)
		{
			if(IsPointOnSegment(j,sy1,sx2,sy2,ex2,ey2))return TRUE;
		}
	}
	else if(sx1 == ex1 && sy1 > ey1)//3
	{
		for ( j = sy1;j >= ey1; j--)
		{
			if(IsPointOnSegment(sx1,j,sx2,sy2,ex2,ey2))return TRUE;
		}
	}

	else if(sx1 < ex1 && sy1 < ey1)//4
	{
		for ( j = sx1,k = sy1; j <= ex1; j++,k++)
		{
			if(IsPointOnSegment(j,k,sx2,sy2,ex2,ey2))return TRUE;
		}
	}
	else if(sx1 > ex1 && sy1 < ey1)//5
	{
		for ( j = sx1,k = sy1; j >= ex1; j--,k++)
		{
			if(IsPointOnSegment(j,k,sx2,sy2,ex2,ey2))return TRUE;
		}
	}
	else if(sx1 > ex1 && sy1 > ey1)//6
	{
		for (j = sx1, k = sy1; j >= ex1; j--,k--)
		{
			if(IsPointOnSegment(j,k,sx2,sy2,ex2,ey2))return TRUE;
		}
	}
	else if(sx1 < ex1 && sy1 > ey1)//7
	{
		for (j = sx1, k = sy1; j <= ex1; j++,k--)
		{
			if(IsPointOnSegment(j,k,sx2,sy2,ex2,ey2))return TRUE;
		}
	}
	return FALSE;
}
void Set1Bit(int* arr, int index)
{
	arr[index/32] = arr[index/32] | BITMASK[index%32];
}
void Set0Bit(int* arr, int index)
{
	arr[index/32] = arr[index/32] & ~BITMASK[index%32];
}

BOOL Is1Bit(int* arr, int index)
{
	if((arr[index/32] & BITMASK[index%32]) == 0)
	{
		return FALSE;
	}
	else
	{
		return TRUE;
	}
}

//高速な計算したい
int GetPoint3(const int stage[STAGE_Y_MAX][STAGE_X_MAX], SCORE_LIST *ScoreList,int ansIndex[Q3_ANS_MAX],int nAns)
{
	int i,j,k,l,m,buf,result = 0;
	int sx,sy,ex,ey;
	int countMap[STAGE_Y_MAX][STAGE_X_MAX] = {0};

	if(nAns <=0 )return -1;

	
	for( i = 0; i < nAns; i++)
	{
		for( j = 0; j < nAns; j++)
		{
			if(!Is1Bit(ScoreList->m_score[ansIndex[i]].m_kaburi,ansIndex[j]) && i != j)
			{
				break;
			}
			//重なっている位置を求める
		}

		if(j == nAns) //重なっていないやつだけ計算
		{
			buf = 0;
			for( j = 0; j < nAns; j++)
			{
				if(ScoreList->m_score[ansIndex[i]].m_score == ScoreList->m_score[ansIndex[j]].m_score && i != j)
				{
					printf("ERRORアルゴリズムに問題の可能性あり\n");
					buf = ScoreList->m_score[ScoreList->count].m_score;
					for(k=0; k < GetKeta(ScoreList->m_score[i].m_score); k++)
					{
						buf *= 10;
					}
				}
			}
			result += ScoreList->m_score[ansIndex[i]].m_score + buf;
		}
		else //重なっている
		{
			for (k = 0; k <= ScoreList->m_score[ansIndex[i]].m_isPair; k++)
			{
				sx = ScoreList->m_score[ansIndex[i]].m_ansPtr[k].sx;
				sy = ScoreList->m_score[ansIndex[i]].m_ansPtr[k].sy;
				ex = ScoreList->m_score[ansIndex[i]].m_ansPtr[k].ex;
				ey = ScoreList->m_score[ansIndex[i]].m_ansPtr[k].ey;
				//IsPointOnSegmentを利用する
				if(sx < ex && sy == ey)//0
				{
					for ( l = sx;l <= ex; l++)
					{
						countMap[sy][l]++;
					}
				}
				else if(sx == ex && sy < ey)//1
				{
					for ( l = sy;l <= ey; l++)
					{
						countMap[l][sx]++;
					}
				}
				else if(sx > ex && sy == ey)//2
				{
					for ( l = sx;l >= ex; l--)
					{
						countMap[sy][l]++;
					}
				}
				else if(sx == ex && sy > ey)//3
				{
					for ( l = sy;l >= ey; l--)
					{
						countMap[l][sx]++;
					}
				}
				else if(sx < ex && sy < ey)//4
				{
					for ( l = sx,m = sy; l <= ex; l++,m++)
					{
						countMap[m][l]++;
					}
				}
				else if(sx > ex && sy < ey)//5
				{
					for ( l = sx,m = sy; l >= ex; l--,m++)
					{
						countMap[m][l]++;
					}
				}
				else if(sx > ex && sy > ey)//6
				{
					for (l = sx, m = sy; l >= ex; l--,m--)
					{
						countMap[m][l]++;
					}
				}
				else if(sx < ex && sy > ey)//7
				{
					for (l = sx, m = sy; l <= ex; l++,m--)
					{
						countMap[m][l]++;
					}
				}
			}
		
		}
	}

	for( i = 0; i < nAns; i++)
	{
		for( j = 0; j < nAns; j++)
		{
			if(!Is1Bit(ScoreList->m_score[ansIndex[i]].m_kaburi,ansIndex[j]) && i != j)
			{
				break;
			}
		}

		if(j == nAns) //重なっていないやつだけ計算
		{
		}
		else //重なっている
		{
			for (k = 0; k <= ScoreList->m_score[ansIndex[i]].m_isPair; k++)
			{
				buf = 0;
				sx = ScoreList->m_score[ansIndex[i]].m_ansPtr[k].sx;
				sy = ScoreList->m_score[ansIndex[i]].m_ansPtr[k].sy;
				ex = ScoreList->m_score[ansIndex[i]].m_ansPtr[k].ex;
				ey = ScoreList->m_score[ansIndex[i]].m_ansPtr[k].ey;
				//IsPointOnSegmentを利用する
				if(sx < ex && sy == ey)//0
				{
					for ( l = sx;l <= ex; l++)
					{
						if(countMap[sy][l] <= 1)
						{
							buf *= 10;
							buf += stage[sy][l];
						}
					}
				}
				else if(sx == ex && sy < ey)//1
				{
					for ( l = sy;l <= ey; l++)
					{
						if(countMap[l][sx] <= 1)
						{
							buf *= 10;
							buf += stage[l][sx];
						}
					}
				}
				else if(sx > ex && sy == ey)//2
				{
					for ( l = sx;l >= ex; l--)
					{
						if(countMap[sy][l] <= 1)
						{
							buf *= 10;
							buf += stage[sy][l];
						}
					}
				}
				else if(sx == ex && sy > ey)//3
				{
					for ( l = sy;l >= ey; l--)
					{
						if(countMap[l][sx] <= 1)
						{
							buf *= 10;
							buf += stage[l][sx];
						}
					}
				}
				else if(sx < ex && sy < ey)//4
				{
					for ( l = sx,m = sy; l <= ex; l++,m++)
					{
						if(countMap[m][l] <= 1)
						{
							buf *= 10;
							buf += stage[m][l];
						}
					}
				}
				else if(sx > ex && sy < ey)//5
				{
					for ( l = sx,m = sy; l >= ex; l--,m++)
					{
						if(countMap[m][l] <= 1)
						{
							buf *= 10;
							buf += stage[m][l];
						}
					}
				}
				else if(sx > ex && sy > ey)//6
				{
					for (l = sx, m = sy; l >= ex; l--,m--)
					{
						if(countMap[m][l] <= 1)
						{
							buf *= 10;
							buf += stage[m][l];
						}
					}
				}
				else if(sx < ex && sy > ey)//7
				{
					for (l = sx, m = sy; l <= ex; l++,m--)
					{
						if(countMap[m][l] <= 1)
						{
							buf *= 10;
							buf += stage[m][l];
						}
					}
				}

				result += buf;
			}
		
		}
	}
	return result;
}

//簡易版GetPoint……重ならない前提、ペアはm_scoreを利用
int EasyGetPoint(SCORE_LIST *ScoreList,int ansIndex[Q3_ANS_MAX],int nAnsIndex)
{
	int i,result = 0;
	for (i = 0; i < nAnsIndex; i++)
	{
		result += ScoreList->m_score[ansIndex[i]].m_score;
	}
	return result;
}

//アンサーリスト関数
