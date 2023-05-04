#include <string.h>
#include "esp_log.h"
#include "wally_core.h"
#include "wally_bip39.h"
#include "wallet.h"
#include "helpers.h"

char *wallet_err_to_name(wallet_err_t response)
{

    switch (response)
    {
    case 0:
        return "WALLET_OK";
        break;
    case 1:
        return "WALLET_ERROR";
        break;
    default:
        return "UNKNOW_ERROR";
        break;
    }
}
