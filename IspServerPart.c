#include"head.h"


void* ispServerPart() {
	char frame[MAX_FRAME_SIZE] = { 0 };
	responseFrame* rpf= (responseFrame*)calloc(sizeof(responseFrame), 1);//给用户的回应帧
	requestionFrame* rf = (requestionFrame*)calloc(sizeof(requestionFrame), 1);//用户发来的请求帧
	

	while (1) {
		struct sockaddr_in recvAddr;
		int recvAddrLen=sizeof(recvAddr);
		rf->sizeOfFrame = recvfrom(socketWithIsp, rf->frame, sizeof(rf->frame), 0, (struct socketaddr*)&recvAddr, &recvAddrLen);
		if (rf->sizeOfFrame <= 0) {
			continue;
		}
		printf("\nframe from superior :");
		printCharToBinary(rf->frame, rf->sizeOfFrame);
		rpf = processFrame(rf->frame, rf->sizeOfFrame);

		//将dns上级服务器的相应帧存入数据库
		addIpAndDomain(rf->domain, rf->ip);

		//id上锁
		pthread_mutex_lock(&mutex_id);
		//确定发送给哪个用户
		int clientId = 0;
		clientId = (rf->frame[0] >> 4) * 16 * 16 * 16 + (rf->frame[0] & 0b00001111) * 16 * 16 + (rf->frame[1] >> 4) * 16 + (rf->frame[1] & 0b00001111);
		//设置为原有id
		rf->frame[0] = id[clientId].frameId[0];
		rf->frame[1] = id[clientId].frameId[1];
		int cSize = sizeof(id[clientId].addr);
		//通过ispSocket向用户发送
		if (sendto(socketWithClient, rf->frame, rf->sizeOfFrame, 0, (struct sockaddr*)( & id[clientId].addr), &cSize) < 0) {
			perror("Error in sendto");
			exit(EXIT_FAILURE);
		}
		pthread_mutex_unlock(&mutex_id);
		


	}
	
	free(rpf);


}