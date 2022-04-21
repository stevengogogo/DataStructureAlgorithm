#include "FindSimilar.h"




void init_Matrix_ushort(Matrix_ushort* M, int nrow, int ncol){
    ushort **array = malloc(nrow * sizeof *array + (nrow * (ncol * sizeof **array)));
    if(array==NULL){
        printf("Memeory Insufficient: init matrix");
    };
    size_t i;
    ushort * const data = array + nrow;
    for(i = 0; i < nrow; i++){
        array[i] = data + i * ncol;
    }

    M->m = array;
    M->ncol = ncol;
    M->nrow = nrow;
    M->len = (ushort*)calloc(nrow, sizeof(ushort));
}

void kill_Matrix_ushort(Matrix_ushort* M){
    free(M->m);
    free(M->len);
}




void init_FS(infoFs* info){
    init_Matrix_ushort(&info->hstack, Q_RABIN, MAX_N_MAIL);
    info->num_unique = (double*)calloc(MAX_N_MAIL,sizeof(double));
    info->SimList = (double*)calloc(MAX_N_MAIL, sizeof(double));
};

void kill_FS(infoFs* info){
    free(info->num_unique);
    free(info->SimList);
    kill_Matrix_ushort(&info->hstack);
};

void register_hash(infoFs* info, int ID, int hash){
    if(info->hstack.len[hash] != 0){//check duplicate
        int end = info->hstack.m[hash][info->hstack.len[hash]-1];
        if(end == ID){//already appended
            return;
        }
    }

    //Add hash
    info->hstack.m[hash][info->hstack.len[hash]] = ID;
    ++info->hstack.len[hash];

    //Register unique count
    info->num_unique[ID] += 1;
};

/** Return location*/
int popTokenHash(char message[], char token[], int iStr, int* Hash){
    char c;
    int asc; //ascii number
    *Hash = 0; //reset hash value
    //No string left
    if (iStr < 0){
        token[0] = '\0';
        return -1;
    }

    int i = 0; //token[i]
    while(message[iStr] != '\0' ){
        c = message[iStr];
        asc = (int)c; //ascii number

        if (isRegularExpr_ASCII(asc)){
            if (isUpperCase_ASCII(c))
                c = tolower(c);
            token[i] = c;
            ++i;
            ++iStr;
        }
        else{
            if (i==0){
                ++iStr;
                continue;
            }
            else 
                break;
        }

    }

    if (message[iStr] == '\0'){ // EOF
        iStr= -1;
    }

    token[i] = '\0'; //end of token
    *Hash = Hash_RK(token);

    return iStr;
}


void append_mHash(infoFs* info, mail* mails, int ID){
    char* text = mails[ID].content;
    char* subject = mails[ID].subject;
    int hash;
    int iNxt;
    int iStr = 0;
    char token[TOKEN_STRING_LENGTH];

    // Content
    while(1){
        iNxt = popTokenHash(text, token, iStr, &hash);
        if(iNxt==-1){
            break;
        }
        iStr = iNxt;
        register_hash(info, ID, hash);
    }

    //Subject
    iStr = 0;
    while(1){
        iNxt = popTokenHash(subject, token, iStr, &hash);
        if(iNxt==-1){
            break;
        }
        iStr = iNxt;
        register_hash(info,ID, hash);
    }
}

void proc_FS(infoFs* info, mail* mails, int n_mail){
    int ID;
    for(int i=0;i<n_mail;i++){
        ID = mails[i].id;
        append_mHash(info,mails, ID);
    }
}






int Hash_RK(char s[]){
	int i = 0;
	int RK = 0;
	while(s[i]!='\0'){
		RK = (D_RABIN*RK + (int)s[i])%Q_RABIN;
		i++;
	}
	return abs(RK)%Q_RABIN;
}




void answer_FS(infoFs*info, mail* mails, int ID, int n_mail, double threshold, int* list, int* nlist){
    bool isVis[Q_RABIN] = {false};
    double Overlap[MAX_N_MAIL]={0};
    char* text = mails[ID].content;//Remember to add subject
    int iNxt;
    int iStr=0;
    int hash;
    double sim;
    char token[TOKEN_STRING_LENGTH];
    ushort id = (ushort)ID;
    ushort interID;
    *nlist = 0;

    // Content
    while(1){
        iNxt = popTokenHash(text, token, iStr, &hash);
        if(iNxt==-1){
            break;
        }
        iStr = iNxt;

        if(isVis[hash]){
            continue;
        }
        
        //Find similar
        for(int i=0;i<info->hstack.len[hash];i++){
            interID = info->hstack.m[hash][i];
            ++Overlap[(int)interID];
        }
        isVis[hash] = true;
    }

    char* subject = mails[ID].subject; 
    iStr = 0;
    while(1){
        iNxt = popTokenHash(subject, token, iStr, &hash);
        if(iNxt==-1){
            break;
        }
        iStr = iNxt;

        if(isVis[hash]){
            continue;
        }
        
        //Find similar
        for(int i=0;i<info->hstack.len[hash];i++){
            interID = info->hstack.m[hash][i];
            ++Overlap[(int)interID];
        }
        isVis[hash] = true;
    }
    
    // Similarity
    for(int i=0;i<n_mail;i++){
        sim = Overlap[i] / (info->num_unique[i] + info->num_unique[ID]  - Overlap[i]);
        if(sim>threshold && i!=ID){
            list[*nlist]=i;
            ++(*nlist);
        }
    }
}
