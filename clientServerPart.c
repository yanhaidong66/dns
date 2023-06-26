#include"head.h"

void* clientServerPart() {

	char frame[MAX_FRAME_SIZE] = { 0 };
	int id_p = 0;

	while (1) {
		responseFrame* rpf;//给用户的回应帧
		requestionFrame* rf = (requestionFrame*)calloc(sizeof(requestionFrame), 1);//用户发来的请求帧
		
		//接收用户发来的请求帧
		rf->sizeOfFrame = recvfrom(socketWithClient, rf->frame, sizeof(rf->frame), 0, (struct socketaddr*)&clientAddr, &clientAddrLen);
		if (rf->sizeOfFrame < 0) {
			perror("Error in recvfrom");
			continue;
		}


		//处理用户的请求帧
		rpf = processFrame(rf->frame, rf->sizeOfFrame);



		//在db中查找请求的域名对应的ip,如果没找到向isp发送查询
		if (rpf->frame==NULL) {
			//id上锁
			pthread_mutex_lock(&mutex_id);
			//将这个帧的id和ip转换为自定义的id
			frameCopy(id[id_p].frameId, rf->id, 2);
			frameCopy(&id[id_p].addr, &clientAddr, clientAddrLen);
			id_p++;

			if (id_p >= MAX_CONVER_FRAME_SIZE)
				id_p %= MAX_CONVER_FRAME_SIZE;
			pthread_mutex_unlock(&mutex_id);

			//通过和ISP连接的socket向ISP转发查询请求
			if (sendto(socketWithIsp, rf->frame, rf->sizeOfFrame, 0, (const struct sockaddr*)&ispAddr, ispAddrLen) < 0) {
				perror("Error in sendto");
				exit(EXIT_FAILURE);
			}
		}

		//如果找到了向用户返回帧
		else {
			if (sendto(socketWithClient, rpf->frame, rpf->sizeOfFrame, 0, (const struct sockaddr*)&clientAddr, clientAddrLen) < 0) {
				perror("Error in sendto");
				exit(EXIT_FAILURE);
			}

		}
		free(rpf);
	}


}