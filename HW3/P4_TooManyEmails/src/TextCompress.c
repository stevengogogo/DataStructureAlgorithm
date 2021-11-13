#include "TextCompress.h"


void TextCompressMark(char* text, int textlen, que* pinT, que* pinH){
    assert(text[textlen]=='\0');
    int head = textlen-1; //text[textlen] == '\0'
    int tail = 0;
    int hashh, hasht;
    int lenh, lent;
    int Hh, Ht;

    *pinT = init_que(INIT_PIN_SIZE);
    *pinH = init_que(INIT_PIN_SIZE);

    clear_hash(&hashh, &lenh, &Hh);
    clear_hash(&hasht, &lent, &Ht);

    while(head>tail){
        update_hash(text[head], &hashh, &lenh, &Hh, false);
        update_hash(text[tail], &hasht, &lent, &Ht, true);

        if (hashh == hasht){
            if(solve_spurious(text, textlen,tail, head, pinT, pinH)){
            enque(pinT, tail);//'|' on the right
            enque(pinH, head);//'|' on the left
            clear_hash(&hashh, &lenh, &Hh);
            clear_hash(&hasht, &lent, &Ht);
            }
        }
        --head;
        ++tail;
    }

}

bool solve_spurious(char* text, int textlen, int tail, int head, que* pinT, que* pinH){
    char a,b;
    int left_tail = peek_que_rear(pinT);
    int right_head = peek_que_rear(pinH);

    if(left_tail == EMTY_QUE_SIG){left_tail = 0;}
    else{++left_tail;}
    
    if(right_head == EMTY_QUE_SIG){right_head= textlen-1;}
    else{--right_head;}

    int left_len = tail - left_tail + 1;
    int right_len = right_head - head  +1;
    
    assert( left_len == right_len );
    
    for(int i=0;i<left_len;i++){
        a = text[left_tail+i];
        b = text[head+i];
        if(a!=b){return false;}
    }
    return true;
};

void update_hash(char c, int* cur_hash, int* cur_len, int* H, bool rev){
    int asc = str2ascii(c);
    ++(*cur_len);
    int new_hash = ((*H)*asc) % Q_;
    if (rev)
        *cur_hash = (*cur_hash + new_hash) % Q_;
    else{
        *cur_hash = (*cur_hash * D_) % Q_;
        *cur_hash = (*cur_hash + asc) % Q_;
    }
    *H = ((*H)*D_) % Q_;//new hash num
}

void clear_hash(int* cur_hash, int* cur_len, int* H){
    *cur_hash = 0;
    *cur_len = 0;
    *H = 1;
}

void PrintCompressedText(char* text, int textlen, que* pinT, que* pinH){
    int last = peek_que(pinT);
    bool dup = true;//avoid `||`
    for(int i=0;i<textlen;i++){
        
       
        if(i == peek_que_rear(pinH)){
            if(!dup){printf("|"); dup = true;}
            deque_rear(pinH);
        }

        printf("%c", text[i]);
        dup = false;

        if(i==peek_que(pinT)){
            if(!dup){printf("|"); dup = true;}
            deque(pinT);
        }
    }
}

void DisplayCompressedText(char* text){
    int textlen = strlen(text);
    que pinT, pinH;

    TextCompressMark(text, textlen, &pinT, &pinH);
    PrintCompressedText(text, textlen, &pinT, &pinH);

    kill_que(&pinT);
    kill_que(&pinH);
}