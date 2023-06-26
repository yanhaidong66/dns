#include"head.h"


void* ispServerPart() {
	char frame[MAX_FRAME_SIZE] = { 0 };
	responseFrame* rpf= (responseFrame*)calloc(sizeof(responseFrame), 1);//���û��Ļ�Ӧ֡
	requestionFrame* rf = (requestionFrame*)calloc(sizeof(requestionFrame), 1);//�û�����������֡
				

	while (1) {
		rf->sizeOfFrame = recvfrom(socketWithIsp, rf->frame, sizeof(rf->frame), 0, (struct socketaddr*)&ispAddr, &ispAddrLen);
		if (rpf->sizeOfFrame < 0) {
			perror("Error in recvfrom");
			continue;
		}
		rpf = processFrame(rf->frame, rf->sizeOfFrame);

		//��dns�ϼ�����������Ӧ֡�������ݿ�
		addIpAndDomain(rf->domain, rf->ip);

		//ȷ�����͸��ĸ��û�
		struct sockaddr_in converClientAddr;	//ת���Ŀͻ�����ĵ�ַ
		int clientId = 0;
		clientId = (rf->id[0] >> 4) * 16 * 16 * 16 + (rf->id[0] & 0b00001111) * 16 * 16 + (rf->id[1] >> 4) * 16 + (rf->id[1] & 0b00001111);


		//ͨ��ispSocket���û�����
		if (sendto(socketWithClient, rpf->frame, rpf->sizeOfFrame, 0, (const struct sockaddr*)&id[clientId].addr, clientAddrLen) < 0) {
			perror("Error in sendto");
			exit(EXIT_FAILURE);
		}


	}
	
	free(rpf);


}