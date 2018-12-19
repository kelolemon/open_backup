//-------------------------------------------------------------------
//说明：商品管理系统的链表实现框架
//时间：2018.11.20
//其他：1. 关于goodinfo.txt编码问题（存储商品的文件内容有中文）
//        MAC下测试UNICODE无法读取，utf-8中文乱码，GBK和ASCII可以中文正常读写
//        Windows下测试ANSII编码存储的正常
//     2. visualstudio报错fopen等一系列文件操作函数不安全，则在项目-》
//        属性-》预处理器-》预处理器定义处增加_CRT_SECURE_NO_WARNINGS
//任务：1. 完善带有//TO DO YOUR WORK的函数
//     2. 数据结构的实现方式采用链表实现
//     3. 文件的读写参考fileIOreferrence函数
//     4. 注意传链表指针*L和传链表指针的地址**L的区别
//-------------------------------------------------------------------
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

//--------------------------------------------------------------------
//商品的最大数量
//--------------------------------------------------------------------
#define MAX 100
//--------------------------------------------------------------------
//全局变量，存储当前商品的数量
//--------------------------------------------------------------------
int CurrentCnt = 0;
//--------------------------------------------------------------------
//商品信息结构的定义
//--------------------------------------------------------------------
#define MAX_ID_LEN 30
#define MAX_NAME_LEN 30
#define MAX_PRICE_LEN 30
#define MAX_DISCOUNT_LEN 30
typedef struct {
    char	good_id[MAX_ID_LEN];
    char	good_name[MAX_NAME_LEN];
    int  	good_price;
    char	good_discount[MAX_DISCOUNT_LEN];
    int		good_amount;
    int		good_remain;
}GoodInfo;

//--------------------------------------------------------------------
//定义商品链表的结点
//--------------------------------------------------------------------
typedef struct node
{
    GoodInfo data;
    struct node *next;
}GoodList;

//--------------------------------------------------------------------
//参考函数：本函数用于提供文件读写的参照
//--------------------------------------------------------------------
void fileIOreferrence(void)
{
    char tempstring[30];

    //定义文件操作的指针
    FILE *fp;
    //fopen用于打开文件，接收两个参数，一个是文件的路径，一个是文件打开的方式
    //例如xxxxxx.txt和该项目的可执行文件在同一目录下，则此处只需要所读取内容文件名
    //例如r代表以只读方式打开文件
    fp = fopen("xxxxxxx.txt", "r"); 
    //如果w代表打开只写文件，若文件存在则长度清为0，即该文件内容消失，若不存在则创建该文件
    //其余打开方式请自行查阅文档
    fp = fopen("xxxxxxx.txt", "w");

    //fscanf用于从txt文件中读取内容，下例以字符串形式读入一段字符并存放在tempstring中
    fscanf(fp, "%s", tempstring);
    //或者以格式化的方式读入字符串
    fscanf(fp, "\t%s\n", tempstring);

    //fprintf以格式化的方式向txt文件中写入内容
    fprintf(fp, "%s\t", tempstring);

    //检查文件内容是否已经读到文件结束符了
    while ( !feof(fp))
    {
        //…………
    }

    //最后需要使用fclose关闭文件指针
    fclose(fp);
}

//--------------------------------------------------------------------
//检查商品文件是否存在或者是否为空
//--------------------------------------------------------------------
bool check_nullfile(void)
{
    FILE *fp = fopen("goodinfo.txt", "r");
    //file not exist
    if (!fp) {
        printf("商品信息初始化文件不存在！程序将为您新建一个.\n");
        FILE *fp = fopen("goodinfo.txt", "w");
        fclose(fp);
        return false;
    }
        //file already exist
    else {
        int temp;
        //res for try to read file if file null feof() can't determine whether file is null or not
        int res = fscanf(fp, "%d", &temp);
        fclose(fp);
        if (res <= 0)
            return false;
        else
            return true;
    }
}

//--------------------------------------------------------------------
//以行读取输入的信息
//--------------------------------------------------------------------
int read_line(char str[], int n)
{
    int ch, i = 0;

    while (isspace(ch = getchar()))
        ;
    while (ch != '\n' && ch != EOF) {
        if (i < n)
            str[i++] = ch;
        ch = getchar();
    }
    str[i] = '\0';
    return i;
}
//-------------------------------------------------------------
//打印单个商品链表节点的信息 
//-------------------------------------------------------------
void Goodprint(GoodList *p){
    /**
     * 1.打印单个链表商品结点的信息
     */
    printf("\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    printf("ID:%s\t名称:%s\t价格:%d\t折扣:%s\t数量:%d\t剩余:%d\n",p->data.good_id,p->data.good_name,p->data.good_price,p->data.good_discount,p->data.good_amount,p->data.good_remain);
    printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    //TO DO YOUR WORK

    //    输出格式参考：
    //    printf("\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    //    printf("ID:%s\t名称:%s\t价格:%s\t折扣:%s\t数量:%d\t剩余:%d\n",
    //           ……………………);
    //    printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n"); 
}
//--------------------------------------------------------------------
//释放商品链表
//--------------------------------------------------------------------
void DestroyGoods(GoodList **L) {
    /**
     * 1.使用free函数依次free掉L的所有节点
     */
    GoodList* last=*L;
    for (GoodList *p=*L;;p=p->next){
        if (p==*L) continue;
        last->next=NULL;
        free(last);
        last=p;
        if (!p->next){
            free(p);
            break;
        }
    }
    //TO DO YOUR WORK
}

//--------------------------------------------------------------------
//删除商品文件以及商品链表中的所有信息
//--------------------------------------------------------------------
void DelAll(GoodList **L) {
    /**
     * 1.清空存储商品内容的文件
     * 2.清空商品链表，销毁已有的节点，并新建一个空链表头
     */
    FILE* file=fopen("goodinfo.txt","w");
    fprintf(file,"-1");
    fclose(file);
    DestroyGoods(L);
    GoodList* head=*L;
    head->next=NULL;
    CurrentCnt=0;
    //TO DO YOUR WORK
}

//--------------------------------------------------------------------
//读取商品文件goodinfo.txt的内容,并建立链表L
//--------------------------------------------------------------------
void info_init(GoodList **L) {
     /**
     * 1.判断goodinfo.txt是否存在，不存在则新建一个goodinfo.txt
     * 2.在未达到文件尾的情况下，从文件中读取商品信息
     * 3.然后新建链表
     * 文件信息的读写可参照fileIOreferrence函数
     */
    if (check_nullfile()){
        FILE* p = fopen("goodinfo.txt","r");
        for(;!feof(p);){
            char id[30];
            char name[30];
            int price;
            char discount[30];
            int amount;
            int remain;
            fscanf(p,"%s\t",id);
            fscanf(p,"%s\t",name);
            fscanf(p,"%d\t",&price);
            fscanf(p,"%s\t",discount);
            fscanf(p,"%d\t",&amount);
            fscanf(p,"%d\n",&remain);
            GoodList* h;
            h=(struct node *)malloc(sizeof(GoodList));
            strcpy(h->data.good_id,id);
            h->data.good_amount=amount;
            strcpy(h->data.good_discount,discount);
            strcpy(h->data.good_name,name);
            h->data.good_price=price;
            h->data.good_remain=remain;
            h->next=NULL;
            GoodList* t=*L;
            if (t==NULL) *L=h;
            else{
                for(;t->next;) t=t->next;
                t->next=h;
            }
            CurrentCnt++;
        }
        fclose(p);
    }
    printf("商品的链表文件已建立，有%d个商品记录\n", CurrentCnt);
}

//--------------------------------------------------------------------
//将当前商品链表中的内容存入商品文件goodinfo.txt，存盘后销毁链表L
//--------------------------------------------------------------------
void info_flush(GoodList **L) {
    /**
     * 1.将链表内容写入到goodinfo.txt
     * 2.销毁链表
     * 3.商品数量置0
     * 文件信息的读写可参照fileIOreferrence函数
     */
    FILE* file=fopen("goodinfo.txt","w");
    if (CurrentCnt)
    for (GoodList *p=*L;;p=p->next){
        if (p==*L) continue;
        fprintf(file,"%s\t%s\t%d\t%s\t%d\t%d\n",p->data.good_id,p->data.good_name,p->data.good_price,p->data.good_discount,p->data.good_amount,p->data.good_remain);
        if (!p->next) break;
    }
    fclose(file);
    if (CurrentCnt==0) printf("提示：未写入任何商品信息到Goodinfo.txt文件\n");
    else printf("提示：%d个商品信息存入Goodinfo.txt文件\n", CurrentCnt);
    //TO DO YOUR WORK
   
    //    输出内容参考：
    //    if .... printf("提示：%d个商品信息存入Goodinfo.txt文件\n", savecount);
    //    else printf("提示：未写入任何商品信息到Goodinfo.txt文件\n");
    DestroyGoods(L);
    CurrentCnt=0;
}

//--------------------------------------------------------------------
//在屏幕上输出所有商品信息
//--------------------------------------------------------------------
void OutputAll(GoodList *L)
{
     /**
     * 1.对链表内容进行读取，然后输出商品信息
     */
    //TO DO YOUR WORK
    if (!L->next) {puts("没有商品信息");return;};
    for (GoodList* p=L;;p=p->next) {
        if (p == L) continue;
        printf("\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
        printf("ID:%s\t名称:%s\t价格:%d\t折扣:%s\t数量:%d\t剩余:%d\n",p->data.good_id,p->data.good_name,p->data.good_price,p->data.good_discount,p->data.good_amount,p->data.good_remain);
        printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
        if (!p->next) break;
    }
}

//--------------------------------------------------------------------
//添加一条商品记录
//--------------------------------------------------------------------
void info_insert(GoodList **L) {
    /**
     * 1.接收输入的某一条商品的信息，包括ID、名称、价格、折扣、数量、剩余
     * 注：首先通过scanf()函数读入待插入的商品信息的每项数据以换行符来区分信息中的每个条目
     *    分配大小商品信息结构体的内存空间，然后将读入的数据分别拷贝到已分配得到的内存中，
     *    其中字符串的拷贝调用系统函数strcpy。
     *    另外：可以使用前面自定义的read_line函数进行行数据读取
     * 2.分别实现头插法、尾插法，中间位置插入三种，
     * 3.然后根据用户输入的插入方式进行相应的节点位置插入
     * 4.【选作】ID号在插入的时候需要进行查重，如果已经有该ID号了，提示重复
     */
    GoodList *p=(struct node *) malloc(sizeof(GoodList));
    puts("输入你要插入的商品信息:");
    printf("商品id:");scanf("%s",p->data.good_id);
    if (CurrentCnt)
    for (GoodList *i=*L;;i=i->next) {
        if (i == *L) continue;
        if (strcmp(i->data.good_id, p->data.good_id) == 0) {
            puts("错误！该ID已经存在");
            return;
        }
        if (!i->next) break;
    }
    printf("商品名称:");scanf("%s",p->data.good_name);
    printf("商品价格:");scanf("%d",&p->data.good_price);
    printf("商品折扣:");scanf("%s",p->data.good_discount);
    printf("商品数量:");scanf("%d",&p->data.good_amount);
    printf("商品剩余:");scanf("%d",&p->data.good_remain);
    puts("请输出你要插入的位置，0为尾部，1为头部，i为第i个位置");
    int pos=0;scanf("%d",&pos);
    if (pos<0){
        puts("error! please put a positive number or zero!");
        return;
    }
    if (pos>CurrentCnt+1) pos=0;
    if (pos==0){
        GoodList* end=*L;
        for(;end->next;end=end->next);
        end->next=p;p->next=NULL;
    }else
    if (pos==1){
        GoodList* head=*L;
        p->next=head->next;
        head->next=p;
    }else{
        GoodList* tmp=*L;
        for (int i=0;i<pos-1;i++) tmp=tmp->next;
        p->next=tmp->next;
        tmp->next=p;
    }
    puts("插入成功！");
    CurrentCnt++;
    // TO DO YOUR WORK
}

//--------------------------------------------------------------------
//删除一条商品记录
//--------------------------------------------------------------------
void info_dele(GoodList **L) {
    /**
     * 1.输入商品的名称，如果名称存在则删除商品信息，即释放对应指针所指向的内存，
     *   并且将该指针赋值为空，然后打印出删除成功的提示
     * 2.如果输入的商品名称不存在则出现商品不存在的提示
     */
    puts("输入需要删除商品ID，-1退出查找");
    char id[30];scanf("%s",id);
    char ex[30];
    strcpy(ex,"-1");
    int flag=0;
    if (strcmp(id,ex)==0) return ;
    GoodList *last=*L;
    if (CurrentCnt)
    for (GoodList *p=*L;;p=p->next){
        if (p==*L) continue;
        if (strcmp(p->data.good_id,id)==0){
            printf("\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
            printf("ID:%s\t名称:%s\t价格:%d\t折扣:%s\t数量:%d\t剩余:%d\n",p->data.good_id,p->data.good_name,p->data.good_price,p->data.good_discount,p->data.good_amount,p->data.good_remain);
            printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
            printf("是否删除该商品（Y/N）");
            char ch;
            for (ch=getchar();ch!='Y' && ch!='N' && ch!='y' && ch!='n';ch=getchar()) puts("Please input Y/N");
            if (ch=='N' || ch=='n') return;
            last->next=p->next;
            p->next=NULL;
            free(p);
            p=NULL;
            CurrentCnt--;
            printf("Tips:删除id为%s的商品成功\n",id);
            printf("Tips:现在还有%d个商品信息\n",CurrentCnt);
            flag=1;
            break;
        }
        last=p;
        if (!p->next) break;
    }
    if (!flag) puts("您要删除的商品不存在！");
    return;
    // TO DO YOUR WORK
}

//--------------------------------------------------------------------
//查找一条商品记录
//--------------------------------------------------------------------
void info_search(GoodList *L) {
    /**
     * 1.输入商品的名称，如果名称存在则打印商品信息
     * 2.如果商品不存在则提示商品不存在
     */
    puts("输入需要查找的商品名称，-1退出查找");
    char name[30];scanf("%s",name);
    char ex[30];
    strcpy(ex,"-1");
    int flag=0;
    if (strcmp(name,ex)==0) return ;
    if (CurrentCnt)
    for (GoodList *p=L;;p=p->next){
        if (p==L) continue;
        if (strcmp(p->data.good_name,name)==0){
            printf("\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
            printf("ID:%s\t名称:%s\t价格:%d\t折扣:%s\t数量:%d\t剩余:%d\n",p->data.good_id,p->data.good_name,p->data.good_price,p->data.good_discount,p->data.good_amount,p->data.good_remain);
            printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
            flag=1;
            break;
        }
        if (!p->next) break;
    }
    if (!flag) puts("您要查找的商品不存在！");
    return;
    // TO DO YOUR WORK
}

//--------------------------------------------------------------------
//修改一条商品记录
//--------------------------------------------------------------------
void info_change(GoodList **L) {
     /**
     * 1.输入商品的名称，如果名称存在则打印商品信息
     * 2.然后用户输入新的商品信息
     * 3.如果要修改的商品存在并且信息输入结束后则出现修改成功并且重新打印出软件选择界面
     */
    puts("输入需要修改商品ID，-1退出查找");
    char id[30];scanf("%s",id);
    char ex[30];
    strcpy(ex,"-1");
    int flag=0;
    if (strcmp(id,ex)==0) return ;
    if (CurrentCnt)
    for (GoodList *p=*L;;p=p->next){
        if (p==*L) continue;
        if (strcmp(p->data.good_id,id)==0){
            printf("\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
            printf("ID:%s\t名称:%s\t价格:%d\t折扣:%s\t数量:%d\t剩余:%d\n",p->data.good_id,p->data.good_name,p->data.good_price,p->data.good_discount,p->data.good_amount,p->data.good_remain);
            printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
            puts("输入新的商品信息:");
            printf("商品id:");scanf("%s",p->data.good_id);
            printf("商品名称:");scanf("%s",p->data.good_name);
            printf("商品价格:");scanf("%d",&p->data.good_price);
            printf("商品折扣:");scanf("%s",p->data.good_discount);
            printf("商品数量:");scanf("%d",&p->data.good_amount);
            printf("商品剩余:");scanf("%d",&p->data.good_remain);
            puts("商品修改成功，修改后的信息为:");
            printf("\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
            printf("ID:%s\t名称:%s\t价格:%d\t折扣:%s\t数量:%d\t剩余:%d\n",p->data.good_id,p->data.good_name,p->data.good_price,p->data.good_discount,p->data.good_amount,p->data.good_remain);
            printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
            flag=1;
            break;
        }
        if (!p->next) break;
    }
    if (!flag) puts("您要修改的商品不存在！");
    return;
    // TO DO YOUR WORK
}

//--------------------------------------------------------------------
//冒泡排序实现对链表节点的排序
//--------------------------------------------------------------------
void bubble_sort(GoodList **L) {
     /**
     * 1.采用冒泡排序对商品链表进行排序，按照价格从低到高进行排序
     * 2.然后输出排序后的商品链表
     */
     GoodList* head=*L;
     for (GoodList* p=head->next;p;p=p->next)
         for (GoodList* q=p->next;q;q=q->next){
             if (p->data.good_price > q->data.good_price){
                 GoodInfo tmp=p->data;
                 p->data=q->data;
                 q->data=tmp;
             }
         }
     printf("当前共有%d个商品",CurrentCnt);
     for (GoodList* p=head->next;p;p=p->next) Goodprint(p);
     // TO DO YOUR WORK
}

//--------------------------------------------------------------------
//主函数
//--------------------------------------------------------------------
int main()
{
     /**
     * 1.初始化一个链表
     * 2.循环显示商品管理系统的操作选择列表
     * 3.用户选择后调用相应的函数进行处理，处理完成后再度显示系统选择列表
     * 4.如果选择超出列表范围，则默认退出系统不存盘。
     */
    GoodList *head=(struct node *)malloc(sizeof(GoodList));
    head->next=NULL;
    info_init(&head);
    for(;;) {
        puts("超市商品管理系统");
        puts("****************************************");
        puts("1.显示所有商品信息:");
        puts("2.修改某个商品信息:");
        puts("3.插入某个商品信息:");
        puts("4.删除某个商品信息:");
        puts("5.查找某个商品信息:");
        puts("6.商品存盘并退出系统:");
        puts("7.对商品的价格进行排序:");
        puts("8.（慎用）删除所有内容:");
        puts("其他.不存盘并退出系统:");
        puts("****************************************");
        puts("输入您的选择:");
        int n = 0;
        scanf("%d", &n);
        if (n == 1) OutputAll(head);
        else if (n == 2) info_change(&head);
        else if (n == 3) info_insert(&head);
        else if (n == 4) info_dele(&head);
        else if (n == 5) info_search(head);
        else if (n == 6) {
            info_flush(&head);
            break;
        }
        else if (n == 7) bubble_sort(&head);
        else if (n == 8) DelAll(&head);
        else {DestroyGoods(&head);break;}
        puts("****************************************");
    }
    // TO DO YOUR WORK
    return 0;
}