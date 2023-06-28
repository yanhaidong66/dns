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
		pthread_mutex_lock(&mutex_socketWithClient);
		rf->sizeOfFrame = recvfrom(socketWithClient, rf->frame, sizeof(rf->frame), 0, (struct socketaddr*)&clientAddr, &clientAddrLen);
		pthread_mutex_unlock(&mutex_socketWithClient);
		if (rf->sizeOfFrame <= 0) {
			continue;
		}


		//处理用户的请求帧
		int result= processFrame(rf->frame, rf->sizeOfFrame,rpf,rf);

		if (arg.level == 1) {
			pthread_mutex_lock(&mutex_arg);
			printf("\n--------------------------------------\n");
			printf("frame_id:");
			printCharToBinary(rf->id,4);
			
			printf("client_ip:");
			char clientIp[MAX_LEN_IP] = { 0 };
			// 将clientAddr.sin_addr转换为字符串
			inet_ntop(AF_INET, &(clientAddr.sin_addr), clientIp, sizeof(clientIp));
			printf("%s", clientIp);

			printf("\nclient_port:");
			int clientPort =  0 ;
			// 将clientAddr.sin_addr转换为字符串
			clientPort = clientAddr.sin_port;
			printf("%d", clientPort);

			printf("\nsearch_domain:%s\n",rf->domain);
			printf("--------------------------------------\n");
			pthread_mutex_unlock(&mutex_arg);
		}

		if (arg.level == 2) {
			pthread_mutex_lock(&mutex_arg);
			printf("\n--------------------------------------\n");
			//printCharToBinary(rf->frame,rf->sizeOfFrame);
			printf("frame_id:");
			printCharToBinary(rf->id, 2);

			printf("client_ip:");
			char clientIp[MAX_LEN_IP] = { 0 };
			// 将clientAddr.sin_addr转换为字符串
			inet_ntop(AF_INET, &(clientAddr.sin_addr), clientIp, sizeof(clientIp));
			printf("%s", clientIp);

			printf("\nclient_port:");
			int clientPort = 0;
			// 将clientAddr.sin_addr转换为字符串
			clientPort = clientAddr.sin_port;
			printf("%d", clientPort);

			printf("\nsearch_domain:%s\n", rf->domain);
			

			printf("qr:%d", rf->qr );
			
			printf("\nopcode:%d",rf->opcode);
			
			printf("\naa:%d",rf->aa);
			
			printf("\ntc:%d", rf->tc );
			
			printf("\nrd:%d", rf->rd );
			
			printf("\nra:%d",rf->ra);
			
			printf("\nrcode:%d",rf->rcode);

			printf("\nquestionCount:%d", rf->questionCount);

			printf("\nanswerCount:%d", rf->answerCount);

			printf("\nadditionCount:%d", rf->additionCount);

			printf("\nauthority:%d", rf->authorityCount);
			
			printf("\n--------------------------------------\n");
			pthread_mutex_unlock(&mutex_arg);

		}

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
			//printf("\nconver frame:\n");
			//printCharToBinary(rf->frame, rf->sizeOfFrame);
			

 			if (id_p >= MAX_CONVER_FRAME_SIZE-2)
				id_p %= MAX_CONVER_FRAME_SIZE;
			pthread_mutex_unlock(&mutex_id);

			//通过和ISP连接的socket向ISP转发查询请求
			int r = 0;
			pthread_mutex_lock(&mutex_socketWithIsp);
			if ((r=sendto(socketWithIsp, rf->frame, rf->sizeOfFrame, 0, (const struct sockaddr*)&ispAddr, ispAddrLen)) < 0) {
				printf("socket send conver frame to ISP :Error in sendto %d",r);
				
			}
			pthread_mutex_unlock(&mutex_socketWithIsp);
		}
		else if (result == -1) {
			//将返回的rcode设置为3,返回为错误码
			rf->frame[3] = rf->frame[3] | 0b00000111;
			//将rq设置为1，表示为响应报文
			rf->frame[2] = rf->frame[2] | 0b10000000;
			if (sendto(socketWithClient, rf->frame, rf->sizeOfFrame, 0, (const struct sockaddr*)&clientAddr, clientAddrLen) < 0) {
				perror("send to client : Error in sendto");
			}
		}

		//如果找到了向用户返回帧
		else {
			if (sendto(socketWithClient, rpf->frame, rpf->sizeOfFrame, 0, (const struct sockaddr*)&clientAddr, clientAddrLen) < 0) {
				perror("send to client : Error in sendto");
				
			}

		}
		
		
	}


}