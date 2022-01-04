#include "LdapClient.h"
#include <ldap.h>

#include <string.h>
#include <iostream>


LdapClient::LdapClient(const std::string& URI, const std::string& searchbase)
        :URI(URI), searchbase(searchbase), handle(nullptr), version(LDAP_VERSION3), connected(false)
{

}

LdapClient::~LdapClient()
{
    ldap_unbind_ext_s(handle , nullptr, nullptr);
}


void LdapClient::connect()
{
    int returnCodeInit = ldap_initialize(&handle, URI.data());
    if(returnCodeInit != LDAP_SUCCESS)
        throw LdapClientException("Initialization of ldap client failed (" + std::to_string(returnCodeInit)  + ") : " + std::string(ldap_err2string(returnCodeInit)));

    int returnCodeOptions = ldap_set_option(handle, LDAP_OPT_PROTOCOL_VERSION, &version);
    if(returnCodeOptions != LDAP_OPT_SUCCESS)
        throw LdapClientException("Setting ldap version failed (" + std::to_string(returnCodeOptions) + ") : " + std::string(ldap_err2string(returnCodeOptions)));

    int returnCodeEncryption = ldap_start_tls_s(handle, nullptr, nullptr);
    if(returnCodeEncryption != LDAP_SUCCESS)
        throw LdapClientException("Starting secure connection failed (" + std::to_string(returnCodeEncryption) + ") : " + std::string(ldap_err2string(returnCodeEncryption)));

    connected = true;
}

bool LdapClient::authenticateUser(const std::string& username, const std::string& password)
{
    if(username.empty() || password.empty())
        throw LdapClientException("Error: username and password cannot be empty");

    if(username.length() > MAX_USERNAME_LENGTH)
        throw LdapClientException("Error: username length cannot exceed " + std::to_string(MAX_USERNAME_LENGTH));

    BerValue cred;
    cred.bv_val = (char*) password.data();
    cred.bv_len = password.length();

    std::string bindUsername = "uid=" + username + ",ou=people,dc=technikum-wien,dc=at";

    int returnCodeAuthentication = ldap_sasl_bind_s(handle, bindUsername.data(), LDAP_SASL_SIMPLE, &cred, nullptr, nullptr, nullptr);

    if(returnCodeAuthentication == LDAP_INVALID_CREDENTIALS)
        return false;

    if(returnCodeAuthentication != LDAP_SUCCESS)
        throw LdapClientException("User Authentication failed (" + std::to_string(returnCodeAuthentication) + ") : " + std::string(ldap_err2string(returnCodeAuthentication)));

    return true;
}
