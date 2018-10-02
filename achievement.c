#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//author： EugeneJie 

struct students{	//结构体数组存放录入的学生信息 
	long num;	//学号 
	char name[10];	//姓名 
	int score[6];	//每门课程成绩 
}student[30];
void exchange(int rs,int ms,int i,int j)	//整体交换录入的学生信息 
{
	int k,t1;
	long t2;
	char t3[10];
	t2=student[i].num;				//交换学号 
	student[i].num=student[j].num;
	student[j].num=t2;
	strcpy(t3,student[i].name);		//交换姓名 
	strcpy(student[i].name,student[j].name);
	strcpy(student[j].name,t3);
	for(k=0;k<ms;k++)				//交换各科成绩
	{
		t1=student[i].score[k];
		student[i].score[k]=student[j].score[k];
		student[j].score[k]=t1;
	}
}
void luru(int rs,int ms)	//手动录入
{
	int i,j; 
	printf("请输入学生的学号和姓名----\n");
	for(i=0;i<rs;i++)
	{
		printf("第%d位学生：",i+1);
		scanf("%ld%s",&student[i].num,&student[i].name);
		printf("请录入%ld %s的%d门课程的考试成绩:\n",student[i].num,student[i].name,ms); 
		for(j=0;j<ms;j++)
			scanf("%d",&student[i].score[j]); 
	}
	printf("录入成功！\n");
}
void jisuan(int rs,int ms)	//计算每门课程的总分和平均分
{
	int i,j,sum[6]={0};
	float aver[6];
	for(i=0;i<ms;i++)	//计算每门课程总分和平均分 
	{
		for(j=0;j<rs;j++)
			sum[i]+=student[j].score[i];
		aver[i]=sum[i]*1.0/rs;
	}
	printf("\t总分\t平均分\n");
	for(i=0;i<ms;i++)
		printf("课程%d\t%d\t%.1f\n",i+1,sum[i],aver[i]);
		
	}
void mingci(int rs,int ms)	//按学生总分由高到低排出名次表 
{
	int t1,i,j,sum[30]={0};
	long t2;
	char t3[10];
	for(i=0;i<rs;i++)		//计算每个学生的总分 
		for(j=0;j<ms;j++)
			sum[i]+=student[i].score[j];
	for(i=0;i<rs-1;i++)		//根据学生总分冒泡排序 
		for(j=i+1;j<rs;j++)
			if(sum[i]<sum[j])
			{
				t1=sum[i];	//交换总分 
				sum[i]=sum[j];
				sum[j]=t1;
				exchange(rs,ms,i,j); 
			}
	printf("名次\t学号\t姓名\t总分\n");	//输出名次表
	for(i=0;i<rs;i++)
		printf("%2d    %-8ld %s\t%d\n",i+1,student[i].num,student[i].name,sum[i]); 
}
void chengji(int rs,int ms)
{
	int i,j,k,t1,sum[30]={0};
	long t2;
	char t3[10];
	for(i=0;i<rs-1;i++)		//根据学生学号冒泡排序 
		for(j=i+1;j<rs;j++)
			if(student[i].num>student[j].num)
				exchange(rs,ms,i,j);
	for(i=0;i<rs;i++)		//计算每个学生的总分  
		for(j=0;j<ms;j++)
			sum[i]+=student[i].score[j];
	printf("  学号\t  姓名");	//输出成绩表 
	for(i=0;i<ms;i++)
		printf("\t课程%d",i+1);
	printf("\t总分\n"); 
	for(i=0;i<rs;i++)
	{
		printf("%-8ld %s",student[i].num,student[i].name);
		for(j=0;j<ms;j++)
			printf("\t%d",student[i].score[j]);
		printf("\t%d\n",sum[i]);
	}
}
void query(int rs,int ms)	//按姓名查询学生排名及其考试成绩 
{
	int i,j,k,count,flag=0,t1,sum[30]={0};
	long t2;
	char t3[10];
	for(i=0;i<rs;i++)		//计算每个学生的总分 
		for(j=0;j<ms;j++)
			sum[i]+=student[i].score[j];
	for(i=0;i<rs-1;i++)		//根据学生总分冒泡排序 
		for(j=i+1;j<rs;j++)
			if(sum[i]<sum[j])
			{
				t1=sum[i];	//交换总分 
				sum[i]=sum[j];
				sum[j]=t1;
				exchange(rs,ms,i,j);
			}
	printf("请输入学生姓名：");
	scanf("%s",&t3);
	for(i=0,count=0;i<rs;i++,count++)
		if(strcmp(t3,student[i].name)==0)
		{
			flag=1; 
			break;
		}
	if(flag)	//判断有无此学生 
	{
		printf("  学号\t  姓名");	//输出成绩表 
		for(i=0;i<ms;i++)
			printf("\t课程%d",i+1);
		printf("\t总分\t名次\n");
		printf("%-8ld %s",student[count].num,student[count].name);
		for(j=0;j<ms;j++)
			printf("\t%d",student[count].score[j]);
		printf("\t%d\t%d\n",sum[count],count+1);
	}
	else printf("未查询到此学生成绩，请检查是否输入正确！\n") ;
	
}
void statistics(int rs,int ms)	//对每门课程分别统计每个类别的人数以及所占的百分比
{
	int i,j,c1,c2,c3,c4,c5;
	printf("\t优秀\t\t良好\t\t中等\t\t及格\t\t不及格\n");
	for(i=0;i<ms;i++)
	{	
		c1=c2=c3=c4=c5=0;	//计数器归零 
		for(j=0;j<rs;j++)
			if(student[j].score[i]<60) c5++;
			else if(student[j].score[i]<70) c4++;
			else if(student[j].score[i]<80) c3++;
			else if(student[j].score[i]<90) c2++;
			else c1++;
		printf("课程%d",i+1); 
		printf("\t%d (%.1f%%)",c1,c1*100.0/rs); 
		printf("  \t%d (%.1f%%)",c2,c2*100.0/rs); 
		printf("  \t%d (%.1f%%)",c3,c3*100.0/rs); 
		printf("  \t%d (%.1f%%)",c4,c4*100.0/rs); 
		printf("  \t%d (%.1f%%)",c5,c5*100.0/rs); 
		printf("\n");
	}
}
void output(int rs,int ms)
{
	int i,j,k,t1,sum[30]={0};
	long t2;
	char t3[10];
	float aver[30];
	for(i=0;i<rs-1;i++)	//根据学生学号冒泡排序 
		for(j=i+1;j<rs;j++)
			if(student[i].num>student[j].num)
				exchange(rs,ms,i,j); 
	for(i=0;i<rs;i++)	//计算每个学生的总分和平均分 
	{
		for(j=0;j<ms;j++)
			sum[i]+=student[i].score[j];
		aver[i]=sum[i]*1.0/ms;
	}		
	printf("  学号\t  姓名");	//输出成绩表 
	for(i=0;i<ms;i++)
		printf("\t课程%d",i+1);
	printf("\t总分\t平均分\n"); 
	for(i=0;i<rs;i++)
	{
		printf("%-8ld %s",student[i].num,student[i].name);
		for(j=0;j<ms;j++)
			printf("\t%d",student[i].score[j]);
		printf("\t%d\t%.1f\n",sum[i],aver[i]);
	}
}
int* read()	//读取学生信息 
{
	FILE *fp;
	int i,j,rs,ms;
	static int n[2];	//定义静态数组存储文件中的学生人数和课程门数以返回给主函数 
	char s[50];
	printf("请输入文件名(可包含文件路径)：");
	scanf("%s",&s);
	if((fp=fopen(s,"r"))==NULL)
	{
		printf("文件打开失败，请检查是否输入正确！\n");
		exit(0);
	}
	for(rs=-1;feof(fp)==0;rs++)		//逐行读取学生信息直到文件结束，行数-1(因为录入最后一名学生后仍另起一行)即为学生人数 
		fgets(s,50,fp);
	fseek(fp,18,0); 	//把指针移动到第一行学生姓名之后 
	fgets(s,35,fp);		//读取这行学生成绩使指针移动 
	ms=((int)(ftell(fp))-18)/5;		//指针位置减初始位置除以格式中每门成绩所占字节数即为课程门数 
	rewind(fp);			//使指针回到文件首部 
	for(i=0;i<rs;i++)	//读取并存储学生信息 
	{
		fscanf(fp,"%ld%s",&student[i].num,&student[i].name);
		for(j=0;j<ms;j++)
			fscanf(fp,"%d",&student[i].score[j]);
	}
	fclose(fp);		//关闭文件 
	printf("读取成功！查询到%d名学生的%d门课程的成绩：\n\n",rs,ms);
	chengji(rs,ms);
	n[0]=rs;
	n[1]=ms;
	return n;
 } 
 void write(int rs,int ms)	//将学生信息写入文件 
 {
 	FILE *fp;
 	int i,j;
 	char file[50];
 	printf("请为写入的文件命名(可指定存储路径)：");
 	scanf("%s",&file);
 	if((fp=fopen(file,"w"))==NULL)
 	{
 		printf("文件写入失败，请重试！\n");
 		exit(0);
	}
	for(i=0;i<rs;i++)	//按指定格式将学生信息写入文件 
	{
		fprintf(fp,"%-8ld%10s",student[i].num,student[i].name);
		for(j=0;j<ms;j++)
			fprintf(fp,"%5d",student[i].score[j]);
		fprintf(fp,"\n");
	}
	fclose(fp);		//关闭文件  
	printf("文件写入成功！\n");
 }
int main()
{
	int s,s1,s2,rs,ms,*p;
	system("title 学生成绩管理系统");                       //控制台标题 
	do{														//循环显示菜单 
		printf("\n1.读取文件数据\n");
		printf("2.手动录入\n");
		printf("3.计算每门课程的总分和平均分\n");
		printf("4.按学生总分由高到低排出名次表\n");
		printf("5.按学号由小到大排出成绩表\n");
		printf("6.按姓名查询学生排名及其考试成绩\n");
		printf("7.统计\n");
		printf("8.输出\n");
		printf("9.写入文件\n");
		printf("0.退出系统\n");
		printf("请选择并输入对应的菜单项：");
		scanf("%d",&s);
		if(s==1)											//判断输入的菜单项并执行相应操作 
		{
			p=read();		//p指向存有学生人数和课程门数的数组
			rs=*p;			//*p为学生人数
			ms=*(p+1);		//*(p+1)为课程门数
		}
		else if(s==2) 
		{
			printf("请输入学生人数和课程门数：");
			scanf("%d%d",&s1,&s2);		//为避免输入错误而使变量ms,rs中可能存有的数据丢失 ，因此将输入的数据暂时存放在另外两个变量中 
			if(s1<0||s1>30||s2<0||s2>6)
				printf("输入错误，请重新输入！\n");
			else 
			{
				rs=s1;
				ms=s2; 
				luru(rs,ms);
			}
		}
		else if(s==3) jisuan(rs,ms);
		else if(s==4) mingci(rs,ms);
		else if(s==5) chengji(rs,ms);
		else if(s==6) query(rs,ms);	
		else if(s==7) statistics(rs,ms);
		else if(s==8) output(rs,ms);
		else if(s==9) write(rs,ms);
		else if(s==0) ;
		else printf("输入错误，请重新输入！\n");	
	}while(s!=0);
	return 0;
}
