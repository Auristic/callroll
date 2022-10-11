#include <cstdio> 
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <ctime>

using namespace std;

bool out[20][90] = {0};//���ڱ���out[i][j]��ʾ��i�ڿε�j��ѧ��,1���ڣ�0ȱ�� 
double E;//E = ��Ч������/������
int successRoll;//��Ч������ 
int rollNum;//�������� 

//����lo-hi֮���������������߽� 
int genRandNum(int lo, int hi){
	
	return (rand()%(hi-lo+1))+lo;
}
//��ʼ���������������ݼ� 
void init(void){
	E = 0;
	successRoll = 0;
	rollNum = 0;
	memset(out, 1, sizeof(out));
//	printf("��ʼ����\n");
//	for (int i = 0; i < 20; i++) {
//		printf("��%d�ο�\n", i+1);
//		for (int j = 0; j < 90; j++) {
//			printf("%d ", out[i][j]);
//			if((j+1)%10 == 0)
//				printf("\n");
//		}
//		printf("\n");
//	}
	
	int absentNum = genRandNum(5,8);//ȱ������ 
	//printf("ȱ������%d\n", absentNum);
	int abs[absentNum];//5-8�������� 
	for(int i = 0; i < absentNum; i++){
		int n = genRandNum(0,89);
		//ȥ�� 
		int flag = 0;
		for(int j = 0; j < i; j++){
			if(n==abs[j]){
				i--;
				flag = 1;
				break;
			}
		}
		if(flag == 1)
			continue;
		abs[i] = n;
//		printf("abs[%d]=%d ", i, abs[i]);
	}
	
	//5-8���ض�ȱ��80%�ε� 
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < absentNum; j++) {
			out[i][abs[j]] = 0;//ȱϯ 
		}
	}
	
	//0-3�����ȱ�ε�
	for (int i = 0; i < 20; i++) {
		int cnt = 3;
		while(cnt > 0){
			int j = genRandNum(0, 89);
			if(out[i][j] == 0)//ȥ�� 
				continue;
			out[i][j] = 0;
			cnt--;
		}
	}

	//���ϵ�20%�β���
	for(int k = 0; k < absentNum; k++) {
		//�����Ľ��ϵĿ� 
		int study[4];
		memset(study, -1, sizeof(study));
		for(int i = 0; i < 4; i++){
			int n = genRandNum(0,19);
			//ȥ�� 
			int flag = 0;
			for(int j = 0; j < i; j++){
				if(n==study[j]){
					i--;
					flag = 1;
					break;
				}
			}
			if(flag == 1)
				continue;
			study[i] = n;
//			printf("study[%d]=%d ", i, study[i]);
		}
		for(int i = 0; i < 4; i++){
			out[study[i]][abs[k]] = 1;
		}
	}
	
//	printf("���ڱ�\n");
//	for (int i = 0; i < 20; i++) {
//		printf("��%d�ο�\n", i+1);
//		for (int j = 0; j < 90; j++) {
//			printf("%d ", out[i][j]);
//			if((j+1)%10 == 0)
//				printf("\n");
//		}
//		printf("\n");
//	}
	
}
//û�õ��㷨 
double rollCall(int r){//r��ʾǰr��ȫ���� 
	//ǰr��ȫ����,�ҳ�������5-8���е�1�� 
	int cnt[90];//90��ѧ��ȱ�ڼ���
	int absStu = 0;
	for(int i = 0; i < r; i++){
		for(int j = 0; j < 90; j++){
			if(out[i][j] == 0){
				cnt[j]++;
				successRoll++;
			}
		}
	}
	//�����ҵ�ȱ�������Ǹ�ѧ��
	for(int i = 0; i < 90; i++){
		if(cnt[absStu] < cnt[i])
			absStu = i;
	}
	//��������20-r�ογ�ȫ�����Ǹ�ȱ������ѧ��
	for (int i = r; i < 20; i++){
		if(out[i][absStu] == 0 )
			successRoll++;
	}
	
	//����E�������㷨Ч��
	rollNum = 90*r + 20-r;
	E = (1.0*successRoll)/rollNum;
	printf("\nsuccessRoll = %d\nE = %.4f\n", successRoll, E);
	return E;
}

//��һ�ογ�㣬�㵽û���ĵ�r��ͬѧ�Ͳ����ˣ�������ÿ�οζ������r��û���� 
double rollCall2(int r){
	int absStu[r];
	memset(absStu, -1, sizeof(absStu));
	int cnt=0; 
	for(int j = 0; j < 90; j++){
		rollNum++;
		if(out[0][j] == 0){
			absStu[cnt++] = j;
			successRoll++;
			if(cnt == r)
				break;
		}
	}
	
	for (int i = 1; i < 20; i++){
		for(int j = 0; j < cnt; j++){
			rollNum++;
			if(out[i][absStu[j]] == 0 )
				successRoll++;	
		}
		
	}
	//����E�������㷨Ч��
	E = (1.0*successRoll)/rollNum;
//	printf("successRoll = %d\nrollNum=%d\nE = %.4f\n", successRoll, rollNum, E);
	return E;
}

//���㷽�� 
double fun(double* a, int n)
{
    double* t = a, sum=0;
    double com=0, ave;
    for(int i=0;i<n;i++){
        sum += *(t+i);
    }
    ave = sum * 1.0 / n;
    for (int i = 0; i < n;i++){
        com += (*(a+i) - ave) * (*(a+i) - ave);
    }
    return com/n;
}

int main()
{
	const int testNum = 100000;
	srand((unsigned int)time(NULL));
	for(int r = 1; r <= 5; r++){
		double e = 0;
		//testNum�β��� 
		double k[testNum];
		for(int i = 0; i < testNum; i++){
			init();//�������ݼ� 
			k[i] = rollCall2(r);
			e += k[i];
			
		}
		printf("r=%d  E = %lf ����=%lf\n\n", r, e/testNum, fun(k, testNum));
	}
	return 0;
}
