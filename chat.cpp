#include "chat.h"

#include "iostream"

Chat::Chat()
{
    data_count = 0;
    data = nullptr;

    mem_size = 8;
    data = new AuthData[mem_size];
}
void Chat::reg(char _login[LOGINLENGTH], char _pass[], int pass_length)
{
    uint* digest = sha1(_pass, pass_length);
    addValue(_login, digest);
}

void Chat::del_reg(char _login[LOGINLENGTH])
{
    int index, i = 0;
    for (; i < mem_size; i++) {
        index = hash_func(_login, i * i);
        if (data[index].status == enAuthDataStatus::free)
            return;
        else if (data[index].status == enAuthDataStatus::engaged
            && !memcmp(_login, data[index].login, LOGINLENGTH))
            break;
    }
    if (i >= mem_size) return;

    data[index].status = enAuthDataStatus::deleted;
}


bool Chat::login(char _login[LOGINLENGTH], char _pass[], int pass_length)
{
    int index, i = 0;
    for (; i < mem_size; i++) {
        index = hash_func(_login, i * i);
        if (data[index].status == enAuthDataStatus::free)
            return false;
        else if (data[index].status == enAuthDataStatus::engaged
            && !memcmp(_login, data[index].login, LOGINLENGTH))
            break;
    }
    if (i >= mem_size) return false;

    uint* digest = sha1(_pass, pass_length);

    bool passStatus = !memcmp(data[index].pass_sha1_hash,
        digest,
        SHA1HASHLENGTHBYTES);
    delete[] digest;

    return passStatus;
}

void Chat::addValue(char login[LOGINLENGTH], uint* digest)
{
    int index, i = 0;
    for (; i < mem_size; i++) {
        index = hash_func(login, i * i);
        if (data[index].status == enAuthDataStatus::free)
            break;
    }
    if (i >= mem_size)
    {
        resize();
        addValue(login, digest);
    }
    else {
        data[index] = AuthData(login, digest);
        data_count++;
    }
}

int Chat::hash_func(char login[LOGINLENGTH], int step)
{
    long sum = 0;
    for (int i = 0; i < LOGINLENGTH; i++) {
        sum += login[i];
    }
    return (hf_2(sum) + step) % mem_size;
}

int Chat::hf_2(int val)
{
    const double A = 0.7;
    return int(mem_size * (A * val - int(A * val)));
}

void Chat::resize()
{
    AuthData* save = data;
    int save_ms = mem_size;

    mem_size *= 2;
    data_count = 0;

    for (int i = 0; i < save_ms; i++) {
        AuthData& old_data = save[i];
        if (old_data.status == enAuthDataStatus::engaged) {

            uint* sha_hash_copy = new uint[SHA1HASHLENGTHUINTS];
            memcpy(sha_hash_copy, old_data.pass_sha1_hash, SHA1HASHLENGTHBYTES);

            addValue(old_data.login, sha_hash_copy);
        }
    }

    delete[] save;
}