#ifndef WALLET_H
#define WALLET_H

#ifdef __cplusplus
extern "C"
{
#endif

    typedef enum
    {
        WALLET_OK = 0,
        WALLET_ERROR
    } wallet_err_t;

    char *wallet_err_to_name(wallet_err_t response);

    /**
     * @brief
     */
    int get_languages(void);

#ifdef __cplusplus
}
#endif

#endif