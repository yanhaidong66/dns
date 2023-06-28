#include"head.h"

void* clientServerPart() {

	char frame[MAX_FRAME_SIZE] = { 0 };
	int id_p = 1;

	while (1) {
		responseFrame _rpf = { 0 };
		requestionFrame _rf = { 0 };
		responseFrame* rpf = &_rpf;//给用户的回应帧
		requestionFrame* rf = &_rf;//用户发来的请求帧

		
		//接收用户发来的请求帧
		rf->sizeOfFrame = recvfrom(socketWithClient, rf->frame, sizeof(rf->frame), 0, (struct socketaddr*)&clientAddr, &clientAddrLen);
		if (rf->sizeOfFrame <= 0) {
			continue;
		}


		//处理用户的请求帧
		int result= processFrame(rf->frame, rf->sizeOfFrame,rf,rpf);



		//在db中查找请求的域名对应的ip,如果没找到向isp发送查询
		if (result==0) {
			//id上锁
			pthread_mutex_lock(&mutex_id);
			//将这个帧的id和ip存储到全局变量id结构数组中
			frameCopy(id[id_p].frameId, rf->frame, 2);
			frameCopy(&id[id_p].addr, &clientAddr, clientAddrLen); 
			//将这个帧的dns部分id转换为自定义的id_p
			rf->frame[0] = (char)((0b1111111100000000&id_p)>>8);
			rf->frame[1] = (char)(0b11111111&id_p);
			id_p++;
			////printf("\nconver frame:\n");
			//printCharToBinary(rf->frame, rf->sizeOfFrame);
			

 			if (id_p >= MAX_CONVER_FRAME_SIZE-2)
				id_p %= MAX_CONVER_FRAME_SIZE;
			pthread_mutex_unlock(&mutex_id);

			//通过和ISP连接的socket向ISP转发查询请求
			int r = 0;
			if ((r=sendto(socketWithIsp, rf->frame, rf->sizeOfFrame, 0, (const struct sockaddr*)&ispAddr, ispAddrLen)) < 0) {
				//printf("socket send conver frame to ISP :Error in sendto %d",r);
				exit(EXIT_FAILURE);
			}
		}

		//如果找到了向用户返回帧
		else {
			if (sendto(socketWithClient, rpf->frame, rpf->sizeOfFrame, 0, (const struct sockaddr*)&clientAddr, clientAddrLen) < 0) {
				perror("send to client : Error in sendto");
				exit(EXIT_FAILURE);
			}

		}
		
		
	}


}