#include"head.h"

void* clientServerPart() {

	char frame[MAX_FRAME_SIZE] = { 0 };
	int id_p = 1;

	while (1) {
		responseFrame _rpf = { 0 };
		requestionFrame _rf = { 0 };
		responseFrame* rpf = &_rpf;//���û��Ļ�Ӧ֡
		requestionFrame* rf = &_rf;//�û�����������֡

		
		//�����û�����������֡
		rf->sizeOfFrame = recvfrom(socketWithClient, rf->frame, sizeof(rf->frame), 0, (struct socketaddr*)&clientAddr, &clientAddrLen);
		if (rf->sizeOfFrame <= 0) {
			continue;
		}


		//�����û�������֡
		int result= processFrame(rf->frame, rf->sizeOfFrame,rf,rpf);



		//��db�в��������������Ӧ��ip,���û�ҵ���isp���Ͳ�ѯ
		if (result==0) {
			//id����
			pthread_mutex_lock(&mutex_id);
			//�����֡��id��ip�洢��ȫ�ֱ���id�ṹ������
			frameCopy(id[id_p].frameId, rf->frame, 2);
			frameCopy(&id[id_p].addr, &clientAddr, clientAddrLen); 
			//�����֡��dns����idת��Ϊ�Զ����id_p
			rf->frame[0] = (char)((0b1111111100000000&id_p)>>8);
			rf->frame[1] = (char)(0b11111111&id_p);
			id_p++;
			////printf("\nconver frame:\n");
			//printCharToBinary(rf->frame, rf->sizeOfFrame);
			

 			if (id_p >= MAX_CONVER_FRAME_SIZE-2)
				id_p %= MAX_CONVER_FRAME_SIZE;
			pthread_mutex_unlock(&mutex_id);

			//ͨ����ISP���ӵ�socket��ISPת����ѯ����
			int r = 0;
			if ((r=sendto(socketWithIsp, rf->frame, rf->sizeOfFrame, 0, (const struct sockaddr*)&ispAddr, ispAddrLen)) < 0) {
				//printf("socket send conver frame to ISP :Error in sendto %d",r);
				exit(EXIT_FAILURE);
			}
		}

		//����ҵ������û�����֡
		else {
			if (sendto(socketWithClient, rpf->frame, rpf->sizeOfFrame, 0, (const struct sockaddr*)&clientAddr, clientAddrLen) < 0) {
				perror("send to client : Error in sendto");
				exit(EXIT_FAILURE);
			}

		}
		
		
	}


}