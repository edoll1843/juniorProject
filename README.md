# 딥러닝 기반 CCTV 녹화동영상 대상 이미지 검색 기술 개발

### 2020 소프트웨어융합대학 산학연계SW프로젝트 전시회 우수상 수상
### 2020 소프트웨어융합대학 컴퓨터정보공학부 졸업작품 전시회 최우수상 수상
팀장 : 이정호
컴퓨터정보공학부
2014722038
edoll1843@naver.com

팀원 : 김광호
컴퓨터정보공학부
2014722072
chollian34@naver.com

팀원 : 윤상민
컴퓨터정보공학부
2014722062
sseemmiin@naver.com

발표 영상 : https://www.youtube.com/watch?v=JFufYgtSUNs

1. 과제의 개요
 
1.1. 배경 및 필요성

	 - 프로젝트 신청 배경 
	  ﹡ 인공지능 산업 생태계 육성을 위해 정부 차원의 전략 수립 및 투자 확대 및 연구개발 지원
	  ﹡ 인력 부족으로 인한 CCTV 사각지대 발생 및 인공지능 기반 CCTV 기술의 효율성과 필요성 인지
	  ﹡ AI기반 이미지 처리 및 영상분석 기술기반 맞춤형 서비스 구축역량 확보의 기회
	  ﹡ 이미지 분석 기술은 주로 기업에서 이뤄지는 현실에 편승하여 앞으로 
	       머신러닝 AI 개발 직군을 준비하기 위한 좋은 기회라 판단

	 - CCTV 관제 요원을 위한 맞춤형 AI 영상분석의 필요성
	  ﹡ CCTV 통합 관제센터의 충분하지 않은 관제인력 실태
	  ﹡ 전체 녹화 영상에서 원하는 목표 추출을 위해 많은 시간과 인력 필요
	  ﹡ AI와 딥러닝의 발전으로 영상분석 기술 고도화

1.2. 목표

	  ﹡ 종래의 CCTV 시스템의 문제 해결 가능
	     ㆍ감시 요원 없이 인공지능을 이용한 CCTV 자동 모니터링
	       - 영상 확인 시간 단축
	       - 특정 객체나 영역 검색 가능
	       - 아파트 관리, 호텔, 백화점, 병원, 방범용 CCTV등 다양한 분야 활용 가능 
	       - 범죄 수사, 범인 추적 등 포렌식 영상분석에서 대량 영상 효과적으로 분석
	  ﹡ 산학연계 SW프로젝트 산출물의 실적화
	      - 프로젝트 간 도출한 아이디어와 알고리즘들의 실사용화 가능
	       ㆍ논문 및 특허화
	       ㆍ인턴쉽 및 현업에서의 활용 
	       ㆍ학습한 내용을 토대로 실무 수행

1.3. 개발의 내용

	  ﹡ MOT20 Dataset을 활용한 YOLO(you only look once)v3 기반의 객체 검출 시스템
	     - 입력 값에 대한 객체 검출 
	     
	       ㆍ사람, 차량에 대한 input
	      
	       ㆍ사람의 경우 95%의 높은 정확도를 보여줌
	       
	       ㆍ어두운 군집 지역에서의 객체 인식률 향상을 위한 MOT20 Dataset 활용
	       
	  ﹡ Hurestic 기법과 RGB 기법을 활용하여 구현한 색채 인식 알고리즘
	  
	      - open cv를 활용한 색채 인식 알고리즘 구현
	      
	       ㆍ사람의 상,하의 구분
	       
	       ㆍcctv 영상에 맞는 색채별 구간 재설정 
	       
	       ㆍ배경색을 제외한 객체의 색만 검출
	       
	  ﹡ 사용하기 편한 유저 인터페이스 및 시스템	
	  
	      - 검색하고자 하는 객체 특징 입력
	      
	      - 윈도우 배치파일을 통한 시스템 구동
	      
	      - 객체 탐색 지점 확인 및 객체 특징 출력
        	  
2. 과제의 내용

가. 설계 및 개발의 내용

1) 개념 설계 (구조 설계)

    시스템 구조도
    
   ![KakaoTalk_20200917_165304360](https://user-images.githubusercontent.com/45708825/93436918-5d615000-f906-11ea-955e-3c0e47cee9b9.png)
  
  2) 상세 설계 (기능 설계)
  
  	  * 객체 검출 엔진
      
	     - MOT20 dataset을 통해 yolov3 학습
	     - Label : person
	     - 기존 YOLOv3는 겹쳐있는 객체와 어두운 지역에서의 인식률이 낮아 해당 부분 개선을 위해 MOT20 Dataset을사용하여 학습시키고 가중치 수정을 통해 겹쳐있는 작은 객체들의 인식률 향상
	     - 객체 검출 이후 각 객체별 image file processing

 	    * 색체 인식 엔진
    
	     - 사람의 상,하의 구분
	     - cctv 영상에 맞는 색채별 구간 재설정 
	     - 배경색을 제외한 객체의 색만 검출
       
  	  * 객체 검색 엔진
    
	     - 사용자가 찾고자 하는 입력값 인지 (사물 , 상,하의 색채)
	     - 입력받은 input을 textfile 형태로 변환
	     - batch file을 통한 객체 검출 엔진과 색체 인식 엔진 동작
	     - 출력 값을 적절히 유저 인터페이스에 배치


3) 개발의 내용
  	  * MOT20 Dataset을 활용한 YOLO(you only look once)v3 기반의 객체 검출 시스템
	     - 입력 값에 대한 객체 검출 
	       ㆍ사람, 차량에 대한 input
	       ㆍ사람의 경우 95%의 높은 정확도를 보여줌
	       ㆍ어두운 군집 지역에서의 객체 인식률 향상을 위한 MOT20 Dataset 활용
	  * Hurestic 기법과 RGB 기법을 활용하여 구현한 색채 인식 알고리즘
	      - open cv를 활용한 색채 인식 알고리즘 구현
	       ㆍ사람의 상,하의 구분
	       ㆍcctv 영상에 맞는 색채별 구간 재설정 
	       ㆍ배경색을 제외한 객체의 색만 검출
	  * 사용하기 편한 유저 인터페이스 및 시스템	 
	      - 검색하고자 하는 객체 특징 입력
	      - 윈도우 배치파일을 통한 시스템 구동
	      - 객체 탐색 지점 확인 및 객체 특징 출력
         	  ﹡ 관련 어플리케이션 개발
        - 오픈소스SW 활용 및 기여

 오픈소스SW 활용
 
	1) 활용한 오픈소스SW 소개
  
	  *YOLO v3
    
	      - object detection은 사전 작업으로 detection을 먼저 수행.
    
	      - object detection을 공간적으로 분리된 bounding box들과 class(분류할object 종류들)에 대한 
		확률과 연관된 regression 문제로 재정의
    
	      - Single neural network는 전체 이미지에서 한번의 평가를 통해서직접적으로
		bounding box들을 예측하고 class의 확률을 계산
    
	      - 전체 detection pipeline이 Single network이기 때문에, 탐지 성능이 최적화됨
        
	      - https://pjreddie.com/darknet/yolo/	 

2) 활용 내용

	  ﹡객체 검출 시스템 구현에 활용

3. 과제의 향후 계획

가. 활용 방안

	  ﹡ 선별관제모니터링 
    
	      - 관제요원의CCTV 채널수 확장
        
	      - 대량 CCTV 대상선별 관리 용이
        
	      - 딥러닝기반 이벤트 관제로 관제요원업무 효율화
        
	      - 객체 세분화 학습시관제 범위 확장

나. 기대 효과

	  *선별관제성능 강화
    
	      - 객체 추가 학습 운용시다양한 객체 유형 검지 가능
        
	      - 객체 학습 데이터보강을 통한 인식율강화
        
	      - 시간대별 ,객체별검색 용이
        
    *관제시스템 확장성

	      - 기존 환경에딥러닝기능 추가로 확장성

  참고문헌: 
	YOLO v3 : AN INCREMENTAL IMPROVEMENT (Joseph Redmon, Ali FarhadiUniversity 	of Washington)


  Youtube 발표 영상 : https://www.youtube.com/watch?v=JFufYgtSUNs
  
