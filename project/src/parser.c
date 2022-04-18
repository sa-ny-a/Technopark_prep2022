#include "../include/parser.h"

Data* init() {
    Data* dt = malloc(sizeof(Data));
    dt->nm_from = (char*)malloc(SIZE_OF_ARRAY);
    dt->nm_to = (char*)malloc(SIZE_OF_ARRAY);
    dt->date = (char*)malloc(SIZE_OF_ARRAY);
    return dt;
}

static int check_string_on_annons(const char* path, const char* control, char* back) {
    FILE *ptr = fopen(path, "r");
    if (ptr == NULL) {
        printf("Not open: ");
        return 0;
    } else {
        char str[SIZE_OF_ARRAY];
        int MRK_STR_FROM = 0;  // Это маркер контроля заголовка, равен 1 когда встретим заголовок
        int MRK_NEWSTR_FROM = 0;  // Это маркер пробела, если сообщение более чем на 1 строку
        while (!feof(ptr)) {
            fgets(str, SIZE_OF_ARRAY, ptr);
            if (strlen(str) > STR_INFO_SIZE) {
                if (MRK_STR_FROM == 0) {
                    size_t check_size = 0;
                    for (size_t j = 0; j < strlen(control); j++) {
                        if (*(str + j) == *(control + j) || *(str + j) == (*(control + j) - 32)) {
                            check_size++;
                        }
                    }
                   if (check_size == strlen(control)) {
                        MRK_STR_FROM = 1;
                    }
                }
                if (MRK_STR_FROM == 1) {
                    if (MRK_NEWSTR_FROM != 1) {
                        for (size_t i = strlen(control) + 1; i < strlen(str); i++) {
                            if (*(str + i) != '\n' && *(str + i) != '\r') {
                                back = strncat(back, &*(str + i), 1);
                            } else {
                                break;
                            }
                        }
                        MRK_NEWSTR_FROM = 1;
                    } else {
                        if (*(str) == ' ') {
                            for (size_t i = 0; i < strlen(str); i++) {
                                if (*(str + i) != '\n' && *(str + i) != '\r') {
                                    back = strncat(back, &*(str + i), 1);
                                } else {
                                    break;
                                }
                            }
                        } else {
                            fclose(ptr);
                            return 1;
                        }
                    }
                }
            }
        }
    }
    fclose(ptr);
    return 0;
}

static int get_key(const char* str, char* key) {
    const char* control_sum = "boundary";
        for (size_t i = 0, check_sum = 0; i < strlen(str) - strlen(control_sum); i++) {
            for (size_t j = 0; j < strlen(control_sum); j++) {
                if (*(str + i + j) == *(control_sum + j) || *(str + i + j) == (*(control_sum + j) - 32)) {
                check_sum++;
                }
            }
            if (check_sum == strlen(control_sum)) {
                for (size_t k = i + strlen(control_sum) + 1; k < strlen(str); k++) {
                    if (*(str + k) != '"') {
                        if (*(str + k) != '\n' && *(str + k) != '\r' && *(str + k) != ' ' && *(str + k) != ';') {
                            key = strncat(key, &*(str + k), 1);
                        } else {
                            break;
                        }
                    }
                }
                return 1;
            }
            check_sum = 0;
        }
    return 0;
}

static int get_score(const char* path, Data* dt) {
    char *key = (char *) malloc(SIZE_OF_ARRAY);
    char *buf = (char *) malloc(SIZE_OF_ARRAY);
    int MRK_KEY = 0;  // Проверка наличия ключа
    int MRK_STR_CONTENT = 1;
    dt->score = 0;
    FILE *email;
    email = fopen(path, "r");
    if (email == NULL) {
        printf("Not open: ");
        return 0;
    } else {
        char str[SIZE_OF_ARRAY];
        Data *trash = init();

        if (MRK_STR_CONTENT == 1) {  // Тут проверяем наличее контента
            if (check_string_on_annons(email, "content-type:", trash->nm_to) == 1) {
                MRK_STR_CONTENT = 0;
                MRK_KEY = get_key(trash->nm_to, key);  // Если ключ еще на этой строке
            }
        } else {
            if (strlen(str) > 10) {
                fgets(str, SIZE_OF_ARRAY, email);
                if (*(str) == ' ' || *(str) == '\t') {  // Работаем уже в поисках ключа
                    MRK_KEY = get_key(str, key);
                }
            }
        }
        fclose(email);
    }
    email = fopen(path, "r");
    if (email == NULL && MRK_KEY == 0) {
        printf("Not open: ");
        return 0;
    } else {
        char str[SIZE_OF_ARRAY];
        while (!feof(email)) {
            fgets(str, SIZE_OF_ARRAY, email);
            if (strlen(str) > 10) {
                if (*(str) == '-' || *(str + 1) == '-') {
                    buf = strcpy(buf, "");
                    for (size_t i = 2; i < strlen(str); i++) {
                        if (*(str + i) != '\n' && *(str + i) != '\r') {
                            buf = strncat(buf, &*(str + i), 1);
                        } else {
                            break;
                        }
                    }
                    if (strcmp(buf, key) == 0) {
                        dt->score += 1;
                    }
                }
            }
        }
        fclose(email);
    }
    if ((MRK_KEY == 0 && MRK_STR_CONTENT == 0) || (MRK_KEY == 0 && MRK_STR_CONTENT == 1)) {
        dt->score = 1;
    }
    return 1;
}

int parser(const char* path) {
    Data* info;
    info = init();
    if (check_string_on_annons(path, "from:", info->nm_from) == 1) {
        printf("%s", info->nm_from);
    }
     if (check_string_on_annons(path, "to:", info->nm_to) == 1) {
        printf("|%s", info->nm_to);
    } else {
        printf("|");
    }
    if (check_string_on_annons(path, "date:", info->date) == 1) {
        printf("|%s", info->date);
    } else {
        printf("|");
    }
    if (get_score(path, info) == 1) {
        printf("|%d\n", info->score);
    } else {
        printf("\n"); 
    }
    return 1;
}
