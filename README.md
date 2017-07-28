 * Practice Data_Structure Using C
 * 자료구조 복습
 * http://blog.naver.com/ljh0326s
 * 
=========================================================================
 * 2017-07-23 
 * 
 * linked-list.c
 * 
 * 알게된 점!!!!! 
 * strdup 문자열 받아서 주소값 반환
 * 헤드포인터는 항상 첫째노드 가리키고 있어야함 그래서 조회할때 새로운 포인터 생성
 * 노드를 삭제하기위해서는 그 전 노드를 알아야 한다. 그래서 새로운 노드를 만들어 따라가게 한다.
 *
=========================================================================
 *
 * 2017-07-24
 * 연결리스트 응용 다항식 
 * polynomial.c
 * 
 * 가정 
 * 1. 다항식의 이름은 x를 제외한 영문 소문자
 * 2. 변수는 항상 x이다.
 * 3. 각 항의 지수는 음이 아닌 정수이고, 계수는 정수이다.
 * 4. 항들이 반드시 차수에 대해 내림차순으로 입력되는 것은 아니며, 동일 차수의 항이 여럿 있을 수도 있다.
 * 5. =, +, - 등의 앞 뒤로 하나 이상의 공백이 있을수도, 없을 수도 있다.
 * 6. 함수는 항상 차수에 대한 내림차순으로 정렬되어 저장되고 출력된다.
 * 7. 동일 이름의 함수를 새로 정의할 수도있다. 이 경우 기존의 함수는 지워진다.
 * 
 * 알게된 점!!!
 * 동적으로 생성된 객체는 초기화가 필요하며 초기화 해주는 함수를 따로 만들어 사용하는 것도 좋은 방법이다.
 * 
 * 아직진행중
 * 
=========================================================================
 * 2017-07-25
 * 연결리스트 응용 다항식 - 완성 디버깅필요
 * 
 * 이중연결리스트
 * 이중연결리스트는 tail필요 -> 마지막 노드 가리킴
 * tail없어도 되지만 그럴꺼면 이중리스트 왜씀? 이중연결리스트를 쓰는 이유 중 하나는 뒤에서부터 앞으로도 갈려고하는 것
 * 
 * 노드 삽입
 * 1. 뉴노드 생성
 * 2. 뉴노드의 next = p
 * 3. 뉴노드의 prev = p -> prev
 * 3. p -> prev -> next = new_node;
 * 4. p -> prev = new_node
 * 
 * 노드 삭제
 * 1. p -> prev -> next = p -> next
 * 2. p -> next -> prev = p -> prev
 * 
 * ---------------------------------------------
 * 시간복잡도와 점근적 분석
 * 
 * 알게된 것!
 * 
 * 좋은 프로그램은?
 * 1.빠른거, 잘 구조화되어있고, 모듈화되어있어서 개선 기능 추가 재사용하기 용이한가, 호완성, 디자인
 * 2. 알고리즘의 자원 사용량 분석(객관적)
 *   2-1. 자원의 종류 : 시간, 메모리, 저장장치, 통신(패킷)
 * 여기서는 실행시간 분석에 대해서만 다룬다.
 
 
 *시간분석?
 *사실 실행 속도는 실행환격에 따라 달라지기 때문에 시간복잡도가 1초다 이런식으로 얘기할 수 없다.
 *그래서 일반적으로 연산의 실행 횟수를 카운트하는 것으로 시간복잡도를 측정한다. 항상이런건 아님
 *그런데 생각해보면 데이터에 따라 비교연산 횟수 달라짐 그래서 입력 데이터의 크기에 대한 함수로 표현한다.
 *그런데 데이터가 같더라도 실제 데이터에 따라 달라질 수 있음(입력 데이터가 같다고 실제 연산이 같지는 않다.)
 *그럼? 다다르다면 그냥 대표값을 이용해서 표현하는게 방법중 하나가 될 것
 *가장 대표적인 대표값 = 평균 
 *그리고 또다른 대표값이 최악의 경우( 다다른데 최악은뭐냐, 탐색에서 데이터가 마지막에 있거나 없는경우) 그럼n번 비교해야지.
 *그런데 평균시간복잡도 분석 어려움 그래서 보통은 최악의 경우 시간복잡도 사용한다.

 * 점근적 분석
 * 실행횟수 카운트할때 정확하게 분석하는게아니라 n*(n-1) + 5 가있다면 n에관한 2차함수기때문에
 * O(n^2)라고 표시함 즉 연산의 최고차항만 남기는거야 보통 빅O라고 읽기도함
 
=========================================================================
  *2017-07-26
  *순환(Recursion)
  *Recursion.java
  *자기 자신을 호출하는 함수 
  *적절한 구조를 갖춰야 무한루프에 빠지지 않는다.
  *
  * 구조의 조건 
  *   1.적어도 하나의 recursion에 빠지지 않는 조건이 존재해야한다.(Bace case라고 부른다.)
  *   2.Recursive case를 통해 반복하다보면 base case에 수렴하게 해야 한다.
  * 
  * 해석 예제
  * public static int func(int n){
      n == 0 ? return 0 : return n + func(n-1);
  }
  * 이 함수의 mission은 0~m까지의 합을 구하는 것이다.
  * n = 0 dlaus gkqdms 0 dlek.
  * n이 0보다 크다면 0에서 n까지의 합은 0에서 n-1까지 합에 n을 더한것이다.
  * 
  ----------------------------------------

  * 순환적으로 사고하기(Recursion Tginking)
  * 반복문으로 해결할수 있는 문제들을 Recursion으로 풀어보자
  * Recursion2.java
  *
1. 문자열 길이계산 길이하나하나 세는게 정석
  *     Recursive로 생각하면 문자열의 길이는 첫번째를 제외한 문자열의 길이 + 1
  * 2. 문자열의 프린트
  *     첫번째 문자를 출력한 후 Recursive로 첫번째 문자를 제외하고 출력한다.
  * 3. 문자열 뒤집어서 프린트
  *     Recursive로 첫번째 글자를 제외하고 프린트 후 첫번째 문자를 출력한다.
  * 4. 배열에있는 숫자 더하기
  *     Recursive로 마지막 데이터 전까지 모두 더한 후 마지막 문자를 더해준다.
  * 5. 파일출력
  *     Recursive로 마지막 데이터 전까지 모두 출력한 후 마지막 문자를 출력한다.
  *     
  * 모든 순환한수는 반복문으로 변경가능하며 그 역도 성립한다.
  * 순환함수는 복잡한 알고리즘을 단순하고 알기쉽게 표현하는 것을 가능하게 하지만
  * 함수 호출에 따른 오버해드가 있다.
  * 
=========================================================================
  *2017-07-27
  *순환(Recursion)3
  *Designing Recursion 순환 설계 하는 방법 및 노하우
  
  *1. 구조가 복잡할수록 기본을 잊지말자
      1-1 적어도 하나의 base case, 즉 순횐되지 않고 종료되는 case가 있어야하고 모든
          case는 결국 base case로 수렴해야 한다.
  
  *2. Recursion으로 프로그래밍 할 때에는 암시적 매개변수를 명시적으로 바꿔주어야 한다.]
      ex) 순차탐색, 첫번째값이 내가 찾는거라면 즉시 반환 아니라면 나머지 타켓을 검색하면된다.
=========================================================================
 *2017-07-28
 *순환 (Recursion)응용 미로탈출
    Maze.java
 *미로찾기 문제를 해결하는 방법은 많으나 순환으로 해결하는게 가장 명확하다.
 *How? Recursive
    - 현제 내가 위치에서 출구까지 가는 경로가 있으려면
    - 1. 현재 위치가 출구거나
    - 2이웃한 셀들 중 하나에서 현재 위치를 지나지 않고 출구까지 가는 경로가 있꺼나
 *일단 Decision problem 문제로 생각해보자
    큰틀
    - 출구면 return true 
    - 출구가 아니고 주위 각 셀(최대4개)이 통로라면 다시 findPath 만약 출구를 찾으면 true 아니면false
 *
    세부내용
    - 내가 방문한 부분과 아닌 부분을 기억해야함 즉 위 큰틀에서 마크를 먼저하고 큰 틀내용을 진행하면 된다.
  
 * 응용2 Counting cells in a Block
 * 문제 : 바이너리 이미지가 주어지면 각 셀이 픽셀에 해당되고 각각 픽셀은 
 * 백그라운드 픽셀이거나 이미지 픽셀(흑백사진) blob는 서로 연결된 이미지 집합
 * 상하좌우 및 대각방향으로도 연결된 것으로 간주
 * 
 *Recursion Thinking
 *현재 픽셀이 속한 blob를 카운트하려면
    1.현재 픽셀이 image픽셀이 아니라면 0 반환
    2.현재 픽셀이 image픽셀이라면 현재픽셀을 카운트한 후
    3.중복 카운트 방지를 위해 다른 색으로 칠하고
    4.현재 픽셀에 이웃한 모든 픽셀들에 대하여 그 픽셀이 속한 blob의 크기를  카운트하여 더해준다. return counter
  
 *응용3 N-queen
   다시공부
-----------------------------------------------------------------
  *트리(Tree)
  *기본용어 노드 레벨, 자식 부모 자손 조상
  *노드가N개인 트리는 항상 N-1개의 링크를 가진다.

  * 이진트리
  * 각각의 노드는 최대 2개의 자식을 갖는다.
  * 자식 노드는 자신의 부모의 왼쪽 자식이지 오른쪽 자식인지가 지정되며 오른쪽 왼쪽이 다르면 서로 다른 노드이다.
  * 이진트리 응용 예 :Expression Tree ,허프만 코드(파일 압축)
  * FUll binary tree 모든 노드가 꽉찬 트리 , complete binary tree 노드가 몇개 비어있지만 왼쪽부터 비어있는 트리
  * full binary tree인 경우 높이가 h면 tree는 2^h-1개의 노드를 갖는다
  * 노드가 N개인 이진트리의 높이는 최악의 경우 N이 된다. 
  * 
  *이진트리 순회(traversal)
  *이진트리 모든 노드 방문 연결리스트는 순서대로 방문하면됨
  *트리는 선형적 구조가아니라 연결리스트 모든 노드 방문할때 다양한 방문이 있을 수 있음
     1. 중순위(inorder)순회
     2. 선순위(preorder)순회
     3. 후순위(postorder)tnsghl
     4. 그외 레벨오더(level-order) 순회