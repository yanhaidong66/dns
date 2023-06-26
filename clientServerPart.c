#include"head.h"

void* clientServerPart() {

	char frame[MAX_FRAME_SIZE] = { 0 };
	int id_p = 0;

	while (1) {
		responseFrame* rpf;//���û��Ļ�Ӧ֡
		requestionFrame* rf = (requestionFrame*)calloc(sizeof(requestionFrame), 1);//�û�����������֡
		
		//�����û�����������֡
		rf->sizeOfFrame = recvfrom(socketWithClient, rf->frame, sizeof(rf->frame), 0, (struct socketaddr*)&clientAddr, &clientAddrLen);
		if (rf->sizeOfFrame < 0) {
			perror("Error in recvfrom");
			continue;
		}


		//�����û�������֡
		rpf = processFrame(rf->frame, rf->sizeOfFrame);



		//��db�в��������������Ӧ��ip,���û�ҵ���isp���Ͳ�ѯ
		if (rpf->frame==NULL) {
			//id����
			pthread_mutex_lock(&mutex_id);
			//�����֡��id��ipת��Ϊ�Զ����id
			frameCopy(id[id_p].frameId, rf->id, 2);
			frameCopy(&id[id_p].addr, &clientAddr, clientAddrLen);
			id_p++;

			if (id_p >= MAX_CONVER_FRAME_SIZE)
				id_p %= MAX_CONVER_FRAME_SIZE;
			pthread_mutex_unlock(&mutex_id);

			//ͨ����ISP���ӵ�socket��ISPת����ѯ����
			if (sendto(socketWithIsp, rf->frame, rf->sizeOfFrame, 0, (const struct sockaddr*)&ispAddr, ispAddrLen) < 0) {
				perror("Error in sendto");
				exit(EXIT_FAILURE);
			}
		}

		//����ҵ������û�����֡
		else {
			if (sendto(socketWithClient, rpf->frame, rpf->sizeOfFrame, 0, (const struct sockaddr*)&clientAddr, clientAddrLen) < 0) {
				perror("Error in sendto");
				exit(EXIT_FAILURE);
			}

		}
		free(rpf);
	}


}