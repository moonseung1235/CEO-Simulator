#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <stdlib.h>

void print_status();
void make_decision();
void settle();
void random_event();
void final_report();
void check_bankrupt();
void investment();
void marketing();
void employment();
void restruction();
void newproduct();
void game();
void event_Lucky();
void event_DataoutFlow();
void event_AttractInvestment();
void event_ServerFailure();
void event_RecruitingKeyTalent();
void event_GovernmentRegulations();
void loading();

double market_share = 5.0;
int turn=1;
int game_continue=1;
// 인덱스:    [0]     [1]    [2]  [3]  [4]
    // 변수명:   money,  user, share, emp, rep
int status[5] = {10000, 5000,   100,  50,  60};
int action[5][5] = {
        // money,  user,  share, employee, reputation
        {-3000,   1000,     20,       10,         10}, // [0] investment
        {-2000,   3000,     10,        0,        -10}, // [1] marketing
        {-2000,      0,     10,       30,         10}, // [2] employment
        { 2500,  -1000,    -10,      -30,        -20}, // [3] restruction
        {-1000,   1000,     30,        0,         20}  // [4] newproduct
};

int event[6][5] = {
        // money,  user,  share, employee, reputation
        {    2000,   1000,     10,        0,          5}, // [0] Lucky
        {-1000,  -1000,    -30,        0,        -30}, // [1] DataoutFlow
        { 3000,      0,     20,        0,         20}, // [2] AttractInvestment
        {-1000,      0,    -20,        0,        -20}, // [3] ServerFailure
        {-2000,      0,      0,       20,         10}, // [4] RecruitingKeyTalent
        {-1000,      0,    -10,        0,        -10}  // [5] GovernmentRegulations
};

int main(int argc, char const *argv[])
{
    SetConsoleOutputCP(CP_UTF8); 
    srand(time(0)); // 랜덤 작동
    game();
    return 0;
}

void game() {
for(int i=0; game_continue!=0 && i<10;i++){
        
        print_status();
        make_decision();
        random_event();
        settle();
        loading();
        check_bankrupt();
    }
final_report();
}

void loading() {
    char a = 0;
     printf("아무 키나 눌러 다음 분기 진행\n");
     scanf("%c", &a);
     getchar();
     printf("다음 분기를 시작합니다.\n");
     
}

void print_status(){
    printf("\n========== %d분기 ==========\n\n",turn);
    printf("자금: %d\n",status[0]);
    printf("사용자: %d\n",status[1]);
    printf("주가: %d\n",status[2]);
    printf("평판: %d\n",status[4]);
    printf("직원: %d\n",status[3]);
    printf("점유율: %.1f%%\n",status[1]/100000.0*100);
    turn++;
}
void make_decision(){
    int choice;
    printf("[1. R&D 투자]  [2. 마케팅]  [3. 채용] [4. 구조조정]  [5. 신제품 출시]\n\n 할 일 선택 >> ");
    scanf("%d", &choice);
    getchar();
    if (choice > 5 || choice <= 0) {
        printf("1~5 사이의 수를 입력해주세요.\n");
        scanf("%d", &choice);
    } 
    switch (choice) {
        case 1 : 
        investment();
        printf("▶ R&D 투자를 진행했습니다. (자금 -3000, 사용자 +1000, 주가 +20, 직원 +10, 평판 +10)\n\n");
        
        break;
        
        case 2 : 
        marketing();
        printf("▶ 마케팅을 진행했습니다.\n(자금 -2000, 사용자 +3000, 주가 +10, 평판 -10)\n\n");
        break;
        
        case 3 : 
        printf("▶ 채용을 진행했습니다.\n(자금 -2000, 주가 +10, 직원 +30, 평판 +10)\n\n");
        employment();
        break;

        case 4 : 
        printf("▶ 구조조정을 진행습니다.\n(자금 +2500, 사용자 -1000, 주가 -10, 직원 -30, 평판 -20)\n\n");
        restruction();
        break;

        case 5 : 
        printf("▶ 신제품 출시를 진행했습니다.\n(자금 -1000, 사용자 +1000, 주가 +30, 평판 +20)\n\n");
        newproduct();
        break;

        default:
        printf("1~5사이 숫자를 입력해주세요.\n");
        
    }
    

}
void settle(){
    int income;
    int expense;
    income = status[1] / 10;
    expense = status[3] * 5;
    status[0] += income;
    status[0] -= expense;
    printf("=== 분기 정산 ===\n");
    printf("사용자 수입: +%d\n", income);
    printf("직원 지출:   -%d\n", expense);
    printf("순수익: %d\n\n", income - expense);
}
void random_event(){
    
    int index = rand() % 6;
    printf("=== 랜덤 이벤트 ===\n");
    switch (index) {
        case 0: event_Lucky();
            printf("▶ 앱이 대박 입소문을 탔습니다!\n(자금 +2000, 사용자 +1000, 주가 +10, 평판 +5)\n\n");
            break;
            
        case 1: event_DataoutFlow();
            printf("▶ 데이터 유출 사고가 발생했습니다!\n(자금 -1000, 사용자 -1000, 주가 -30, 평판 -30)\n\n");
            break;
            
        case 2: event_AttractInvestment();
            printf("▶ 투자 유치에 성공했습니다!\n(자금 +3000, 주가 +20, 평판 +20)\n\n"); 
            break;
            
        case 3: event_ServerFailure();
            printf("▶ 서버 장애가 발생했습니다!\n(자금 -1000, 주가 -20, 평판 -20)\n\n");
            break;

        case 4: event_RecruitingKeyTalent();
            printf("▶ 핵심 인재를 채용했습니다!\n(자금 -2000, 직원 +20, 평판 +10)\n\n");
            break;

        case 5: event_GovernmentRegulations();
            printf("▶ 정부 규제가 강화되었습니다!\n(자금 -1000, 주가 -10, 평판 -10)\n\n");
            break;
}
}
void final_report(){
    if(game_continue<=0){
        printf("펑!\n");
    }else{
        // 등급 및 결과 출력
       int total = 0;
       // 지표들 정규화
       double money_score = status[0] / 100.0;   
        double user_score  = status[1] / 50.0;   
        double share_score = status[2];     
        double cor_score = status[3] * 2.0;      
        double rep_score   = status[4] * 1.6; 
       
        total = money_score + user_score + share_score + cor_score + rep_score;
        char grade = 0;
      
        if (total >=  700) {
         grade = 'S';
       }else if (700 > total && total >= 600) {
         grade = 'A';
       } else if (600 > total && total >= 500) {
         grade = 'B';
       } else if (500 > total && total >= 400) {
         grade = 'C';
       } else if (300 > total && total >= 200) {
         grade = 'D';
       } else if (200 > total && total >= 100) {
        grade = 'E';
       } else {
        grade = 'F';
       }
    printf("\n========== 최종 성과 보고서 ==========\n\n");
    printf("자금: %d\n",status[0]);
    printf("사용자: %d\n",status[1]);
    printf("주가: %d\n",status[2]);
    printf("평판: %d\n",status[4]);
    printf("직원: %d\n",status[3]);
    printf("점유율: %.1f%%\n\n",status[1]/100000.0*100);
    printf("최종 점수: %d\n", total);
    printf("최종 등급: %c\n\n", grade);

    switch(grade){
        case 'S':
            printf("\"세계적인 빅테크 기업으로 성장했습니다!\"\n");
            break;

        case 'A':
            printf("\"유니콘 기업 등극!\"\n");
            break;

        case 'B':
            printf("\"안정적인 성장 기업이 되었습니다.\"\n");
            break;

        case 'C':
            printf("\"평범한 중견 기업 수준입니다.\"\n");
            break;

        case 'D' ... 'E':
            printf("\"간신히 생존에 성공했습니다.\"\n");
            break;
        case 'F':
            printf("\"회사 파산. CEO에서 해고되었습니다.\"\n");
            break;
        default:
            break;
        }
        printf("================================\n\n");
    }

    int c = 0;
    //재시작 혹은 닫기
    printf("재시작: 1, 종료: 2 >>");
    scanf("%d", &c);
    if (c == 1) {
        game_continue = 1;
        status[0] = 10000;
        status[1] = 5000;
        status[2] = 100;
        status[3] = 50;
        status[4] = 60;
        turn = 1;
        game();
    } else if ( c == 2) {
        printf("게임 종료됨\n");
        return;
    }

    
}
void check_bankrupt(){
    if(status[0]<=0){
        printf("파산했습니다!\n");
        game_continue = 0;    
    }
// 사람 지표(사용자user, 동료employee)가 0 이하로 내려가면 0으로 고정
    for (int i  = 1; i<5; i++) {
        if (i % 2 != 0) {
        if (status[i] <= 0) {
            status[i] *= 0;
        }
    }
    }
}
void investment(){
    for(int i=0;i<5;i++){
        status[i]+=action[0][i];
    }
}
void marketing(){
    for(int i=0;i<5;i++){
        status[i]+=action[1][i];
    }
}
void employment(){
    for(int i=0;i<5;i++){
        status[i]+=action[2][i];
    }
}
void restruction(){
    for(int i=0;i<5;i++){
        status[i]+=action[3][i];
    }
}
void newproduct() {
    for(int i=0;i<5;i++){
        status[i]+=action[4][i];
    }
}
void event_Lucky(){
    for(int i=0;i<5;i++){
        status[i]+=event[0][i];
    }
}
void event_DataoutFlow(){
    for(int i=0;i<5;i++){
        status[i]+=event[1][i];
    }
}
void event_AttractInvestment(){
    for(int i=0;i<5;i++){
        status[i]+=event[2][i];
    }
}
void event_ServerFailure(){
    for(int i=0;i<5;i++){
        status[i]+=event[3][i];
    }
}
void event_RecruitingKeyTalent(){
    for(int i=0;i<5;i++){
        status[i]+=event[4][i];
    }
}
void event_GovernmentRegulations(){
    for(int i=0;i<5;i++){
        status[i]+=event[5][i];
    }
}