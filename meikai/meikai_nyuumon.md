
# Table of Contents

1.  [解説](#orge26dc38)
2.  [第3章 プログラムの流れの分岐](#org1a54b04)
    1.  [3-1 if文](#orgb27c8f0)
        1.  [if文・その1](#orgbaa8527)
        2.  [奇数の判定](#org1acafc6)
3.  [第5章 配列](#orgdf3bb68)
    1.  [5-1 配列](#orga95d2c9)
        1.  [配列による成績処理](#org918a481)
        2.  [オブジェクト形式マクロ](#org1014c9f)
4.  [第9章](#org09f126b)
    1.  [9-2 文字例の配列](#orgfbf8079)
        1.  [文字列の配列](#org2e2d812)
        2.  [文字列の配列への文字列の読み込み](#orgde79595)
        3.  [演習9-3](#org472c363)
    2.  [9-3 文字例の操作](#org2d35406)
        1.  [文字列の長さ](#org2590a7f)
        2.  [文字列の表示](#org80ee7c7)
        3.  [数字文字の出現回数](#orgaf28254)
        4.  [大文字・小文字の変換](#orge4f66a0)
        5.  [文字列の配列の受け渡し](#org9ca0146)
    3.  [まとめ](#org5729bac)
5.  [第10章 ポインタ](#org13e0c00)
    1.  [10-1 ポインタ](#orge75ba57)
        1.  [関数の引数](#orga557745)
        2.  [オブジェクトとアドレス](#orgf5b2cc8)
        3.  [アドレス演算子](#orgbb7f038)
        4.  [ポインタ](#orgd9eee83)
        5.  [間接演算子](#orgc14468b)
    2.  [10-2 ポインタと関数](#org57a2673)



<a id="orge26dc38"></a>

# 解説

<http://meikaicansewer.blogspot.com>


<a id="org1a54b04"></a>

# 第3章 プログラムの流れの分岐


<a id="orgb27c8f0"></a>

## 3-1 if文


<a id="orgbaa8527"></a>

### if文・その1


<a id="org1acafc6"></a>

### 奇数の判定


<a id="orgdf3bb68"></a>

# 第5章 配列


<a id="orga95d2c9"></a>

## 5-1 配列


<a id="org918a481"></a>

### 配列による成績処理

1.  List5-9


<a id="org1014c9f"></a>

### オブジェクト形式マクロ

\#define a b
とすると，「この指令以降のaは全てbに置換せよ」という意味．
定義が複数個所に分散しなくて済むので，定義を変更する必要が生じても一括して変えられる．

1.  List5-10

        /*
                学生の点数を読み込んで合計点と平均点を表示（人数をマクロで定義）
        */
        
        #include <stdio.h>
        
        #define NUMBER	5		/* 学生の人数 */
        
        int main(void)
        {
                int i;
                int tensu[NUMBER];	/* NUMBER人の学生の点数 */
                int sum = 0;		/* 合計点 */
        
                printf("%d人の点数を入力してください。\n", NUMBER);
                for (i = 0; i < NUMBER; i++) {
                        printf("%2d番：", i + 1);
                        scanf("%d", &tensu[i]);
                        sum += tensu[i];
                }
        
                printf("合計点：%5d\n", sum);
                printf("平均点：%5.1f\n", (double)sum / NUMBER);
        
                return 0;
        }


<a id="org09f126b"></a>

# 第9章


<a id="orgfbf8079"></a>

## 9-2 文字例の配列

配列の作り方．
名前[行][列]として宣言する．
下の例では，行数は自動的に3になっている．
列数は，最も文字数の多い"Turbo"に合わせ，6となっている（5 + ヌル文字1 = 6）．


<a id="org2e2d812"></a>

### 文字列の配列

1.  List9-6

        #include <stdio.h>
        int main(void)
        {
          int i;
          char cs[][6] = {"Turbo", "NA", "DOHC"};
        
          for (i = 0; i < 3; i++) {
            printf("cs[%d] = \"%s\"\n", i, cs[i]);
          }
          return 0;
        }


<a id="orgde79595"></a>

### 文字列の配列への文字列の読み込み

1.  List9-7

    今度は，scanfでキーボードから読み込んで配列を作る．
    
        /*
                文字列の配列を読み込んで表示
        */
        
        #include <stdio.h>
        
        int main(void)
        {
                int  i;
                char s[3][128];		/* 3は読み込む要素数．128は，何文字入力されるかわからないので，多めに用意している */
                                        /* 実際にはヌル文字が最後にあるので，127文字しか読み込めない */
                for (i = 0; i < 3; i++) {
                        printf("s[%d] : ", i);
                        scanf("%s", s[i]); /* scanfだけど，配列の要素なので&演算子をつけてはだめ． */
                }
        
                for (i = 0; i < 3; i++)
                        printf("s[%d] = \"%s\"\n", i, s[i]);
        
                return 0;
        }


<a id="org472c363"></a>

### 演習9-3

演習9-7を改変

-   文字列の個数を3ではなく大きな数にし，それを[オブジェクト形式マクロ](#org1014c9f)で定義
-   最初のfor文で，"\[\]"を読みこんだら，その時点で読み込みを中断，終了する
-   2番目のfor文では，"\[\]"より前に入力された前文字例を表示する．

    #include <stdio.h>
    
    #define NUMBER 128            /* ここにはセミコロンをつけてはいけない！！！！ */
    
    int main(void)
    {
      int  i, j;
      char s[NUMBER][128];
    
      for (i = 0; i < NUMBER; i++) {
        printf("s[%d] : ", i);
        scanf("%s", s[i]); /* scanfだけど，配列の要素なので&演算子をつけてはだめ． */
    
        for (j = 0; s[i][j] != '\0'; j++) {
          if (s[i][j] != '$') break;
        }
        if (j == 5) break;
      }
    
      for (j = 0; j < i; j++) { /* 1つめのループで止まったiまで，jのループを回すのがポイント */
        printf("s[%d] = \"%s\"\n", j, s[j]);
      }
    
      return 0;
    }


<a id="org2d35406"></a>

## 9-3 文字例の操作


<a id="org2590a7f"></a>

### 文字列の長さ

1.  List9-8

        /*
                文字列の長さを調べる
        */
        
        #include <stdio.h>
        /*--- 文字列strの長さを返す ---*/
        /* まず文字列の長さを取得する関数str_lengthを定義 */
        int str_length(const char s[])	/* const は，定数．値を受け取るだけで，変更はしないことを宣言． */
        {
                int len = 0;
        
                while (s[len])		/* s[len] が非ゼロである間繰り返す．ヌル文字はゼロなので，ループは文字列末尾で止まる．*/
                        len++;
                return len;
        }
        
        int main(void)
        {
                char str[128];	/* ナル文字を含めて128文字まで格納できる */
        
                printf("文字列を入力してください：");
                scanf("%s", str);
        
                printf("文字列\"%s\"の長さは%dです。\n", str, str_length(str));
        
                return 0;
        }

2.  演習9-4

    文字列sを空文字列にする関数を作成せよ．
    
        /*
                文字列を空文字列にする
        */
        
        #include <stdio.h>
        void null_string(char s[])	/* void型の関数なので，returnはできない． */
                                        /* 上手くいっているかを確認する手立てがないので気持ち悪い． */
        {
                int len = 0;
        
                while (s[len]) {
                  len++;
                  s[len] = '\0';
                }
        }
        
        int main(void)
        {
                char str[128];	/* ナル文字を含めて128文字まで格納できる */
        
                printf("文字列を入力してください：");
                scanf("%s", str);
        
                printf("文字列\"%s\"を空文字列にしました。\n", str);
        
                return 0;
        }

3.  演習9-5

    文字列の中に文字cが含まれていれば，その添字を返し，
    含まれていなければ-1を返す関数を作成せよ
    
        #include <stdio.h>
        
        int str_char(const char s[], int c) /* cをintとして扱うことに注意 */
        {
          for (int i = 0; s[i] != '\0'; i++) {
            if (s[i] == c) return i;	/* 整数として扱うのでstr_compしなくていい */
          }
          return -1;
        }
        
        int main(void)
        {
          char str[128];
          int index;
        
          printf("文字列を入力してください: ");  scanf("%s", str);
        
          index = str_char(str, 'c');	/* 文字を整数として扱うときは単引用付！ */
        
          if (index == -1) {
            printf("文字cは含まれていません\n");
          } else {
            printf("文字cは配列の%d番目にあります", index);
          }
        
          return 0;
        }

4.  演習9-6

    文字列sの中に，文字cが含まれている個数（含まれていなければ0とする）を返す関数をら作成せよ
    
        #include<stdio.h>
        
        int str_chnum(const char s[], int c) /* const とcharの間にはコンマを入れてはいけない！ */
        {
          int cnum = 0;
          for (int i = 0; s[i] != '\0'; i++) {
            if (s[i] == c) cnum = cnum + 1;
          }
          return cnum;
        }
        
        int main(void)
        {
          char str[128];		/*要素数の指定を忘れないこと!*/
          int cnum;
        
          printf("文字列を入力してください: ");
          scanf("%s", str);
        
          cnum = str_chnum(str, 'c');
          printf("文字列\"%s\"の中に含まれる\"c\"の数は%d個です．\n", str, cnum);
        
          return 0;
        }


<a id="org80ee7c7"></a>

### 文字列の表示

1.  List9-9

        /*
                文字列を走査して表示する
        */
        
        #include <stdio.h>
        
        /*--- 文字列sを表示（改行はしない）---*/
        void put_string(const char s[])
        {
          int i = 0;
          while (s[i])
                  putchar(s[i++]); /* こんな短縮表記もできるのか...あまりよくないと思うけど．*/
                                   /*そしてputcharは値を返すわけではないので void型でもいいんだな．*/
        }
        
        int main(void)
        {
          char str[128];
        
          printf("文字列を入力してください：");
          scanf("%s", str);
        
          printf("あなたは");
          put_string(str);
          printf("と入力しました。\n");
        
          return 0;
        }

2.  OK 演習9-7

    文字列sをn回だけ連続して表示する関数を作成せよ
    
        #include <stdio.h>
        
        void put_stringn(const char s[], int n)
        {
          int j;
          for (j = 0; j < n; j++) {
            int i = 0;
            while (s[i] != '\0') {
              putchar(s[i]);
              i = i + 1;
            }
          }
        }
        int main(void)
        {
          char str[128];
          int n;
        
          printf("文字列を入力してください:");
          scanf("%s", str);
          printf("\n繰り返したい数を入力してください:");
          scanf("%d", &n);
        
          printf("文字列\"%s\"を%d回繰り返すと", str, n);
          put_stringn(str, n);
          printf("となります．\n");
        
          return 0;
        }
    
    \#+END<sub>SRC</sub>

3.  OK 演習9-8

    文字列を後ろから逆に表示する関数を作成せよ
    
        #include <stdio.h>
        
        void put_stringn(const char s[])
        {
          int i = 0;
          int j;
          while(s[i] != '\0') {
            i++;
          }
          for (j = i -1; j >= 0; j--) {
            putchar(s[j]);
          }
        
        }
        
        int main(void)
        {
          char str[128];
        
          printf("文字列を入力してください: ");
          scanf("%s", str);
        
          printf("あなたが入力した文字列を逆順に表示すると");
          put_stringn(str);
          printf("です．\n");
        
          return 0;
        }


<a id="orgaf28254"></a>

### 数字文字の出現回数

<span class="timestamp-wrapper"><span class="timestamp">[2018-11-30 Fri]</span></span>

1.  OK List9-10

        
        /*
            文字列内の数字文字をカウントする
        */
        
        #include <stdio.h>
        
        /*--- 文字列s内に含まれる数字文字の出現回数を配列cntに格納 ---*/
        void str_dcount(const char s[], int cnt[])
        {
            int i = 0;
            while (s[i]) {
                if (s[i] >= '0' && s[i] <= '9')
                    cnt[s[i] - '0']++;
                i++;
            }
        }
        
        int main(void)
        {
            int  i;
            int  dcnt[10] = {0};	/* {}で囲った数字は初期化子．本文p.114 */
            char str[128];			/* 文字列 */
        
            printf("文字列を入力してください：");
            scanf("%s", str);
        
            str_dcount(str, dcnt);
        
            puts("数字文字の出現回数");
            for (i = 0; i < 10; i++)
                printf("'%d'：%d\n", i, dcnt[i]);
        
            return 0;
        }

2.  OK 演習9-9

    文字列sの文字の並びを反転する関数を作成せよ．
    演習9-8では逆順で「表示するだけ」だったが，今度は書き換える．
    入力したものを書き換えるので危険性が高く，プログラムとしてはあまりよくない．
    
        #include<stdio.h>
        
        void rev_string(char s[])
        {
            int i, length = 0;
            char tmp[128];
            for (i = 0; s[i] != '\0'; i++) {
                tmp[i] = s[i];
                length++;
            }
        
            for (i = 0; i < length; i++) {
                s[i] = tmp[length - i - 1];
            }
        }
        
        int main (void)
        {
            char str[128];
            int i = 0;
            printf("文字列を入力してください:");
            scanf("%s", str);
            /* str = rev_string(str)  こうではなく*/
            rev_string(str);             /* こう書く．*/
        
            printf("あなたが入力した文字列を反転しました．\n");
            printf("その結果は");
            /* while (str[i]) { */
            /*     printf("%s", str[i]); */
            /*     i++; */
            /* } わざわざループを使う必要はない．*/
            printf("%s", str);          /* strを書き換えたのだから，そのまま表示すればいい． */
            printf("です．\n");
        
            return 0;
        }


<a id="orge4f66a0"></a>

### 大文字・小文字の変換

1.  OK List9-11

    <span class="timestamp-wrapper"><span class="timestamp">[2018-12-02 Sun]</span></span>
    
        /*
            文字列内の英字を大文字／小文字に変換
        */
        
        #include <ctype.h>              /* 初めて出てきたライブラリ */
        #include <stdio.h>
        
        /*--- 文字列内の英字を大文字に変換 ---*/
        void str_toupper(char s[])
        {
            int i = 0;
            while (s[i]) {
                s[i] = toupper(s[i]);
                i++;
            }
        }
        
        /*--- 文字列内の英字を小文字に変換 ---*/
        void str_tolower(char s[])
        {
            int i = 0;
            while (s[i]) {
                s[i] = tolower(s[i]);
                i++;
            }
        }
        
        int main(void)
        {
            char str[128];
        
            printf("文字列を入力してください：");
            scanf("%s", str);
        
            str_toupper(str);
            printf("大文字：%s\n", str);
        
            str_tolower(str);
            printf("小文字：%s\n", str);
        
            return 0;
        }
    
    入力された文字列を変更してしまっている点では，恐ろしいプログラムといえる．
    しかも2回も．

2.  解答を見て理解できた 演習9-10

    文字列s内の全ての数字文字を削除する関数を作成せよ．
    例えば，"AB1C9"を受け取ったら，"ABC"に変換する．
    ネットの解答例を見てしまった．
    結構難しい．
    
        #include<ctype.h>
        #include<stdio.h>
        
        void del_digit(char s[])
        {
            int i, j;
        
            for(i = 0; s[i] != '\0'; i++){
                if('0' <= s[i] && s[i] <= '9'){
                    for(j = i; s[j] != '\0'; j++){
                        s[j] = s[j + 1];
                    }
                    i--;
                }
            }
        }
        
        int main(void)
        {
            char str[128];
            printf("文字列を入力してください:");
            scanf("%s", str);
            printf("数字を取り除くと");
            del_digit(str);
            printf("%s", str);
            printf("となります\n");
        
            return 0;
        }


<a id="org9ca0146"></a>

### 文字列の配列の受け渡し

1.  OK List9-12

    このプログラムは文字「列」を3つ，表示している．
    iだけを使った1次元ループ．
    
        /*
            文字列の配列を表示（関数版）
        */
        
        #include <stdio.h>
        
        /*--- 文字列の配列を表示 ---*/
        void put_strary(const char s[][6], int n) /* ここの[6]が，このプログラムの汎用性を損なっている */
        {
            int i;
            for (i = 0; i < n; i++)
                printf("s[%d] = \"%s\"\n", i, s[i]); /* ここは文字列をまるごと，1行ずつ表示している */
        }
        
        int main(void)
        {
            char cs[][6] = {"Turbo", "NA", "DOHC"};
        
            put_strary(cs, 3);
        
            return 0;
        }

2.  OK List9-13

    こちらのプログラムは，「文字」を1つずつ表示している．
    iとjの2次元ループ．
    
        /*
            文字列の配列を表示（関数版：１文字ずつ走査）
        */
        
        #include <stdio.h>
        
        /*--- 文字列の配列を表示（１文字ずつ表示）---*/
        void put_strary2(const char s[][6], int n)
        {
            int i;
            for (i = 0; i < n; i++) {
                int j = 0;
                printf("s[%d] = \"", i);
        
                while (s[i][j])
                    putchar(s[i][j++]); /* 文字「列」ではなく，文字を1つずつ表示している */
        
                puts("\"");
            }
        }
        
        int main(void)
        {
            char cs[][6] = {"Turbo", "NA", "DOHC"};
        
            put_strary2(cs, 3);
        
            return 0;
        }

3.  解答を見て理解できた 演習9-11

    List9-12を以下のように書き換えたプログラムを作成せよ．
    文字列の個数を3ではなく大きな数にし，その値をオブジェクト形式マクロとして定義する．
    文字列の文字数を6ではなく128とする．その値もオブジェクト形式マクロとして定義する．
    文字列の配列を読み込む関数を作成する．[演習9-3](#org472c363)と同様に，ドル記号を5つ読み込んだ時点で読み込みを中断・終了する．
    ドル記号5つより前に入力された全文字列を表示する．
    
        #include <stdio.h>
        
        #define DIM 100
        #define NUMCHAR 128
        
        int main(void)
        {
            char str[DIM][NUMCHAR];
            int i, j, cnt;
            printf("文字列を入力してください\n");
            for (i = 0; i < DIM; i++) {
                cnt = 0;
                printf("%d個目:", i+1);
                scanf("%s", str[i]);
                puts("\n");
                for (j = 0; j < NUMCHAR; j++) {
                    if (str[i][j] != '$') break;
                }
                if (j == 5) break;
            }
            for (j = 0; j < i; j++) {
                printf("%s\n", str[j]);
            }
            return 0;
        }

4.  解答を見て理解できた 演習9-12

    受け取った文字列の配列に格納されているn個の文字列の並びを反転する関数を作成せよ．
    たとえば，sに{"SEC", "ABC"}を受け取ったら，その配列を{"CES", "CBA"}に更新せよ．
    
    1.  林の答案
    
            #include <stdio.h>
            
            void rev_string(char s[][128], int n)
            {
                char tmp[n][128];
                int i, j, length;
                for (i = 0; i < n; i++) {
                    length = 0;
                    for (j = 0; s[i][j] != '\0'; j++) {
                        tmp[i][j] = s[i][j];
                        length++;
                    }
                    for (j = 0; j < length; j++) {
                      s[i][length - j - 1] = tmp[i][j];
                    }
                }
            }
            
            int main(void) {
                int i, n;
                char str[n][128];
                printf("文字列をいくつ入力しますか？");
                scanf("%d", &n);
                for (i = 0; i < n; i++) {
                    printf("%d個目の文字列を入力してください:", i+1);
                    scanf("%s", str[n]);
                    puts("\n");
                }
            
                rev_string(str, n);
            
                printf("その文字列をそれぞれ反転すると");
                for (i = 0; i < n; i++) printf("%s\n", str[i]);
                printf("となります．\n");
            
                return 0;
            }
    
    2.  Web模範解答
    
            #include <stdio.h>
            #define row 128
            
            void rev_string(char s[][128], int n){
                int i, j, length;
                char tmp[128]; /*そうか，tmpは1次元でいいことに気づかなかった*/
            
                for(j = 0; j < n; j++){
            
                    length = 0;
                    for(i = 0; s[j][i] != '\0'; i++){
                        tmp[i] = s[j][i];
                        length++;
                    }
            
                    for(i = 0; i < length; i++){
                        s[j][i] = tmp[length - 1 - i];      
                    }
            
                    printf("s[%d] = \"%s\"\n", j, s[j]);　/*printまでこの関数でやってしまう*/
                }
            }
            
            int main(){
            
                int i, j;
                char cs[row][128];
            
                for(i = 0; i < row; i++){
                    printf("文字列を入力してください：");    scanf("%s", cs[i]);
            
                    for(j = 0; cs[i][j] != '\0'; j++){
                        if(cs[i][j] != '$') break;
                    }
                    if(j == 5) break;
                }
            
                rev_string(cs, i); /*値の更新，表示をすべてここで*/
            
                return 0;
            }
    
    3.  改訂版の答案
    
            #include <stdio.h>
            
            void rev_string(char s[][128], int n)
            {
                char tmp[128];
                int i, j, length;
                for (i = 0; i < n; i++) {
                    length = 0;
                    for (j = 0; s[i][j] != '\0'; j++) {
                        tmp[j] = s[i][j];
                        length++;
                    }
                    for (j = 0; j < length; j++) {
                      s[i][j] = tmp[length - j - 1];
                    }
                    printf("%d個目の文字列: %s\n", i+1, s[i]);
                }
            }
            
            int main(void) {
                int i, n;
                char str[n][128];
                printf("文字列をいくつ入力しますか？");
                scanf("%d", &n);
                for (i = 0; i < n; i++) {
                    printf("%d個目の文字列を入力してください:", i+1);
                    scanf("%s", str[i]);
                    puts("\n");
                }
            
                printf("その文字列をそれぞれ反転すると\n");
                rev_string(str, n);
                printf("となります．\n");
            
                return 0;
            }


<a id="org5729bac"></a>

## まとめ

-   <a id="orgec593c2">ナル文字</a>: 値が0の文字である．8進拡張表記で表記すると'\\0'で，整数定数で表記すると0である．
-   文字列リテラルの末尾にはがナル文字が付加されるので，"ABC"はメモリ上に4バイトを占有し，""でさえも1バイトを消費する．
-   文字列リテラルのバイト数はsizeof()で求める．
-   文字列リテラルには静的記憶域期間が与えられるため，プログラムの開始から終了まで，記憶域を占有する．
-   同じ綴りの文字列リテラルが複数あったときの挙動，つまり1個とみなすのか，別個とみなすかは，処理系によって異なる．
-   文字列の格納先として最適なのはcharの配列である．文字列の末尾は，最初に出現するナル文字．
-   文字列を格納する文字配列の初期化は，char str[] = {'A', 'B', 'C', '\\0'};とするか，char str[] = "ABC";とするかである．
-   文字が1個もない，ナル文字だけの文字列を空文字列という．
-   文字列中の全文字の走査は，先頭文字から始めて，ナル文字に出会うまで順になぞればいい．
-   文字列を走査したとき，ナル文字の前までの文字数が，目に見える文字列の長さ．
-   文字列を画面に表示する時，printfに与える変換指定は%s．
-   キーボードから文字列を読み込む時，scanfに与える変換指定も%s．格納先として与える実引数の配列には，&はつけてはいけない．
-   関数が受け取る文字列は，呼び出した側が与えた配列そのもの．文字列の末尾にちゃんとナル文字があるので，要素数を別の引数として与えなくて大丈夫．
-   文字列を集めた配列は，配列の配列，つまり2次元配列で表せる．たとえば，ナル文字を含めて最大12文字まで格納できる文字列を5個集めた配列は，char ss[5][12];と定義する．ssは2次元配列なので，要素へのアクセスはss[i][j]のように行う．
-   アルファベットの大文字小文字変換はtoupper()とtolower()で行う．どっちも<ctype.h>ライブラリに入っている．これらの関数は，アルファベット以外を勝手にいじることはないので安心して使っていい．


<a id="org13e0c00"></a>

# 第10章 ポインタ


<a id="orge75ba57"></a>

## 10-1 ポインタ


<a id="orga557745"></a>

### 関数の引数

1.  List10-1

    和と差を計算するプログラムを作りたい場合を考える．
    List6-5で学んだ，値渡しの一方通行の法則を忘れていると，下のList10-1のように間違ってしまう．
    仮引数は実引数のコピーでしか無い．
    さらに，関数は1つの値しか返せない．
    この問題の解決に，ポインタの概念が必要．
    \#+NAME list1001
    
        /*
            二つの整数の和と差を求める（間違い）
        */
        
        #include <stdio.h>
        
        /*--- n1とn2の和と差をsumとdiffに格納（間違い）---*/
        void sum_diff(int n1, int n2, int sum, int diff)
        { 
            sum  = n1 + n2;							/* 和 */
            diff = (n1 > n2) ? n1 - n2 : n2 - n1;	/* 差 */
        }
        
        int main(void)
        {
            int na, nb;
            int wa = 0, sa = 0;
        
            puts("二つの整数を入力してください。");
            printf("整数Ａ：");   scanf("%d", &na);
            printf("整数Ｂ：");   scanf("%d", &nb);
        
            sum_diff(na, nb, wa, sa);
        
            printf("和は%dで差は%dです。\n", wa, sa);
        
            return 0;
        }


<a id="orgf5b2cc8"></a>

### オブジェクトとアドレス

オブジェクトはバラバラに保存されるのではなく，1つに連なったメモリ上に存在している．
メモリには，オブジェクトのいろいろな性質も保存されている．
その性質とは，

-   大きさ
-   型
-   記憶域期間（第6章, p.162）
-   識別子

など．

オブジェクトは広いメモリ上に雑居しているので，その場所を特定するために<a id="org33b21d6"></a>が用いられる．


<a id="orgbb7f038"></a>

### アドレス演算子

<a id="orgab19c65"></a>:&のこと．これまでもscanfでよく使っていた．
アドレスを画面上に表示する時には，%pを使う．このpはポインタのp．

    /*
        オブジェクトのアドレスを表示する
    */
    
    #include <stdio.h>
    
    int main(void)
    {
        int    n;
        double x;
        int    a[3];
    
        printf("n   のアドレス：%p\n", &n);
        printf("x   のアドレス：%p\n", &x);
        printf("a[0]のアドレス：%p\n", &a[0]);
        printf("a[1]のアドレス：%p\n", &a[1]);
        printf("a[2]のアドレス：%p\n", &a[2]);
    
        return 0;
    }


<a id="orgd9eee83"></a>

### ポインタ

しかし，アドレスを画面上に表示しても，人間にはあまり有用ではない．
そこで，もっと現実的なプログラムを，ポインタを使って書く．
<a id="org2b16104"></a>とは，あるオブジェクトのアドレスを指すもの．

    /*
        ポインタによって身長を間接的に操作する
    */
    
    #include <stdio.h>
    
    int main(void)
    {
        int sato   = 178;	/* 佐藤宏史君の身長 */
        int sanaka = 175;	/* 佐中俊哉君の身長 */
        int masaki = 179;	/* 真崎宏孝君の身長 */
    
        int *isako, *hiroko;        /* この*を使った宣言方法が，ポインタ型の特徴 */
    
        isako  = &sato;			/* isako はsato　を指す（佐藤君が好き）*/
        hiroko = &masaki;		/* hirokoはmasakiを指す（真崎君が好き）*/
    
        printf("いさ子さんの好きな人の身長：%d\n", *isako);
        printf("ひろ子さんの好きな人の身長：%d\n", *hiroko);
    
        isako = &sanaka;		/* isako はsanakaを指す（気が変わった）*/
    
        *hiroko = 180;			/* hirokoの指すオブジェクトに180を代入 */
                                /* ひろ子さんの好きな人の身長を書きかえる */
    
        putchar('\n');
        printf("佐藤君の身長：%d\n", sato);
        printf("佐中君の身長：%d\n", sanaka);
        printf("真崎君の身長：%d\n", masaki);
        printf("いさ子さんの好きな人の身長：%d\n", *isako);
        printf("ひろ子さんの好きな人の身長：%d\n", *hiroko);
    
        return 0;
    }

ポインタpの値がxのアドレスである時，「pはxを指す」という．


<a id="orgc14468b"></a>

### 間接演算子

<a id="org7d5a708"></a>: \*のこと．
ポインタpがxを指すとき，\*pはxのエイリアスとなる．


<a id="org57a2673"></a>

## 10-2 ポインタと関数

