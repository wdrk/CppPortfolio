안녕하세요.
모든 포트폴리오는 Visual Studio 2017과 FHD 환경에서 개발 및 테스트하였습니다.
각 디렉토리에 있는 실행파일은 x86 Release 모드로 빌드하였습니다.

 - 'visualize the sorting process'는 1부터 300까지의 수를 무작위로 섞은 배열 2개를 만들고, 각각의 배열을 버블정렬과 선택정렬로 정렬하면서 실시간으로 그 과정을 시각화 한 프로그램입니다. 더블버퍼링을 적용했습니다. UI Thread와 Worker Thread를 분리한 구조여서 정렬 도중에 창을 마우스로 드래그하여 이동해도 정렬 과정 그래픽이 멈추지 않습니다.

 - 'HashCalculator'는 WinAPI를 활용하여 프로그램 창 안으로 Drag & Drop을 수행한 한개 혹은 여러개의 파일의 SHA1 값을 계산하여, 각 파일의 절대 경로와 SHA1 해시값을 표시하는 프로그램입니다.

 - 'Multi_Chatting'은 Client 프로그램과 Server 프로그램으로 구성한 터미널 기반의 채팅 프로그램입니다. Client가 접속할때마다 Server가 Thread를 생성하도록 하여 다중 접속이 가능하도록 만들었습니다. Client가 Server에 접속하기 위해서는 Client 코드에 상수로 정의한 IP_ADDRESS 값에 컴퓨터의 로컬 IP 값을 입력하면 됩니다. 접속하면 10개의 Thread를 이용해서 Server에 10번의 접속 요청을 하고 각 Thread마다 메세지를 전송하기 시작합니다. API Hook과 연계하여 테스트하기 위해 Client가 Server에 접속함과 동시에 임의의 메세지를 전송하는 구조입니다.

 - 'API Hook'은 타겟 프로세스에 DLL Injection을 수행한 후 Trampoline hook 기법을 사용해서 타겟 프로세스의 제어 흐름을 변경하는 프로그램입니다. Test용으로 제작한 터미널 기반 채팅 서버 프로그램(타겟 프로그램)의 PID값과 Injection용 DLL이 위치한 경로를 인수로 첨부해서 프로그램을 실행하면 타겟 프로세스의 핸들값을 가져와서 프로세스 내부에 DLL을 추가할 메모리 영역을 확보하고 Thread 생성을 통해 Injection용 DLL을 실행시킵니다. Injection에 성공한 DLL의 내부에서는 send 함수를 호출할때 제가 임의로 만든 MySend로 진입하도록 제어 흐름을 변경하였고, MySend 함수 내부에서 임의의 코드를 거친 후 리턴하기 전에 본래의 send 함수를 호출합니다. Windows API를 사용하므로 Windows OS에서만 동작합니다.

 - 'CVector'는 C++ STL의 Vector가 가진 기능을 직접 구현한 코드입니다. STL Vector의 기능을 똑같이 구현하는 것이 목적인 프로그램이라서 사용자로부터 입력을 받지는 않습니다. 프로그램을 실행하면 main() 함수에 있는 테스트 코드를 거쳐 터미널 화면에 진행 상황 및 결과들을 출력합니다.

 - 'Calculator_with_list_tree_stack' 은 사용자로부터 양의 정수와 '+', '-'로 구성된 계산식을 입력받고 사용자가 입력한 데이터를 이중 연결 리스트로 구성하여 유효성 검사를 합니다. 그 후 이중 연결 리스트의 데이터를 트리 구조로 재구성하여 Post order로 읽어들이고 스택을 구성해서 Post order 순서대로 스택에 push와 pop을 한 뒤 계산값을 출력합니다.
