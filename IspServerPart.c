#include"head.h"


void* ispServerPart() {
	char frame[MAX_FRAME_SIZE] = { 0 };
	
	

	while (1) {
		responseFrame respf = { 0 };
		responseFrame* rpf = &respf;//给用户的回应帧
		struct sockaddr_in recvAddr = { 0 };
		int recvAddrLen=sizeof(recvAddr);
		pthread_mutex_lock(&mutex_socketWithIsp);
		rpf->sizeOfFrame = recvfrom(socketWithIsp, rpf->frame, sizeof(rpf->frame), 0, (struct socketaddr*)&recvAddr, &recvAddrLen);
		if (rpf->sizeOfFrame <= 0) {
			pthread_mutex_unlock(&mutex_socketWithIsp);
			continue;
		}
		pthread_mutex_unlock(&mutex_socketWithIsp);
		
		//printf("\nframe from superior :");
		//printCharToBinary(rpf->frame, rpf->sizeOfFrame);
		getIpAndDomainFromFrame(rpf->frame, rpf->sizeOfFrame,rpf);

		//将dns上级服务器的相应帧存入数据库
		addIpAndDomain(rpf->domain, rpf->ip);

		//id上锁
		pthread_mutex_lock(&mutex_id);
		//确定发送给哪个用户
		int clientId = 0;
		clientId = (rpf->frame[0] >> 4) * 16 * 16 * 16 + (rpf->frame[0] & 0b00001111) * 16 * 16 + (rpf->frame[1] >> 4) * 16 + (rpf->frame[1] & 0b00001111);
		//设置为原有id
		rpf->frame[0] = id[clientId].frameId[0];
		rpf->frame[1] = id[clientId].frameId[1];
		int cSize = sizeof(id[clientId].addr);
		//通过ispSocket向用户发送
		int r = 0;
		pthread_mutex_lock(&mutex_socketWithClient);
 		if ((r=sendto(socketWithClient, rpf->frame, rpf->sizeOfFrame, 0, (const struct sockaddr*) &(id[clientId].addr), cSize)) < 0) {
			perror("Error in sendto to isp\n");
		}
		pthread_mutex_unlock(&mutex_socketWithClient);
		pthread_mutex_unlock(&mutex_id);
		


	}
	


}