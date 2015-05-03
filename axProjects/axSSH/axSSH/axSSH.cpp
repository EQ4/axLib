////
////  axSSH.cpp
////  axSSH
////
////  Created by Alexandre Arsenault on 2015-04-20.
////  Copyright (c) 2015 Alexandre Arsenault. All rights reserved.
////
//
//#include "axSSH.h"
//#include <stdio.h>
//#include <string.h>
//#include <string>
//
//axSSH::axSSH():
//_connected(false)
//{
//    // Open session and set options
//    _session = ssh_new();
//    
////    ssh_blocking_flush(_session, 1000);
////    ssh_set_blocking(_session, 0);
//
//    
//    if (_session == NULL)
//    {
//        exit(-1);
//    }
//}
//
//
//axSSH::~axSSH()
//{
//    ssh_disconnect(_session);
//    ssh_free(_session);
//}
//
//bool axSSH::Connect(const std::string& ip, const std::string& password)
//{
//    ssh_options_set(_session, SSH_OPTIONS_HOST, ip.c_str());
//    
//    // Connect to server
//    int rc = ssh_connect(_session);
//    
//    if (rc != SSH_OK)
//    {
//        fprintf(stderr, "Error connecting to localhost: %s\n",
//                ssh_get_error(_session));
////        ssh_free(_session);
//        
//        _connected = false;
//        return false;
//    }
//    
//    // Verify the server's identity
//    // For the source code of verify_knowhost(), check previous example
//    if (verify_knownhost(_session) < 0)
//    {
//        _connected = false;
//        return false;
//    }
//    
//    // Authenticate ourselves
//    rc = ssh_userauth_password(_session, NULL, password.c_str());
//    
////    if (rc != SSH_AUTH_SUCCESS)
////    {
////        fprintf(stderr, "Error authenticating with password: %s\n",
////                ssh_get_error(_session));
////
////        _connected = false;
////        return false;
////    }
//
//    _connected = true;
//    return true;
//}
//
//int axSSH::verify_knownhost(ssh_session session)
//{
//    unsigned char *hash = NULL;
//    char *hexa;
//    char buf[10];
//    int state = ssh_is_server_known(session);
//    int hlen = ssh_get_pubkey_hash(session, &hash);
//    
//    if (hlen < 0)
//    {
//        return -1;
//    }
//    
//    switch (state)
//    {
//        case SSH_SERVER_KNOWN_OK:
//            break; /* ok */
//        case SSH_SERVER_KNOWN_CHANGED:
//            fprintf(stderr, "Host key for server changed: it is now:\n");
//            ssh_print_hexa("Public key hash", hash, hlen);
//            fprintf(stderr, "For security reasons, connection will be stopped\n");
//            free(hash);
//            return -1;
//        case SSH_SERVER_FOUND_OTHER:
//            fprintf(stderr, "The host key for this server was not found but an other"
//                    "type of key exists.\n");
//            fprintf(stderr, "An attacker might change the default server key to"
//                    "confuse your client into thinking the key does not exist\n");
//            free(hash);
//            return -1;
//        case SSH_SERVER_FILE_NOT_FOUND:
//            fprintf(stderr, "Could not find known host file.\n");
//            fprintf(stderr, "If you accept the host key here, the file will be"
//                    "automatically created.\n");
//            /* fallback to SSH_SERVER_NOT_KNOWN behavior */
//        case SSH_SERVER_NOT_KNOWN:
//            hexa = ssh_get_hexa(hash, hlen);
//            fprintf(stderr,"The server is unknown. Do you trust the host key?\n");
//            fprintf(stderr, "Public key hash: %s\n", hexa);
//            free(hexa);
//            if (fgets(buf, sizeof(buf), stdin) == NULL)
//            {
//                free(hash);
//                return -1;
//            }
//            if (strncasecmp(buf, "yes", 3) != 0)
//            {
//                free(hash);
//                return -1;
//            }
//            if (ssh_write_knownhost(session) < 0)
//            {
//                fprintf(stderr, "Error %s\n", strerror(errno));
//                free(hash);
//                return -1;
//            }
//            break;
//        case SSH_SERVER_ERROR:
//            fprintf(stderr, "Error %s", ssh_get_error(session));
//            free(hash);
//            return -1;
//    }
//    free(hash);
//    return 0;
//}
//
//std::string axSSH::Request(const std::string& command)
//{
//    
//    axPrint(command);
//    
//    ssh_session session = _session;
//    
//    
//    char buffer[256];
//    unsigned int nbytes;
//    ssh_channel channel = ssh_channel_new(session);
//    
//    if (channel == nullptr)
//    {
//        axPrint("Error :", ssh_channel_new);
//        return "Error";
//    }
//    
//    int rc = ssh_channel_open_session(channel);
//    
//    if(rc == SSH_AGAIN)
//    {
//        axPrint("ssh_channel_open_session : AGAIN");
//
//    }
//    else if (rc == SSH_OK)
//    {
//        axPrint("ssh_channel_open_session : OK");
//
//    }
//    else
//    {
//        axPrint("Error : ssh_channel_open_session");
////        ssh_channel_send_eof(channel);
////        ssh_channel_free(channel);
//        ssh_channel_close(channel);
//        return "Error";
//    }
//    
//    
//    // Set non blocking.
//    ssh_set_blocking(_session, 0);
//    
//    
//    bool loop_request = false;
//    int loop_count = 0;
//    
//    do
//    {   
//        if(loop_count > 100000)
//        {
////            ssh_channel_send_eof(channel);
////            ssh_channel_free(channel);
//            ssh_channel_close(channel);
//            axPrint("Error : Too many loop.");
//            return "Error";
//        }
//        
//        rc = ssh_channel_request_exec(channel, command.c_str());
//        
//        switch(rc)
//        {
//            case SSH_AGAIN:
//                axPrint(loop_count, " SSH_AGAIN");
//                loop_request = true;
//                break;
//                
//            case SSH_OK:
//                axPrint("SSH_OK");
//                loop_request = false;
//                break;
//                
//            default:
//                axPrint("Error request");
//                loop_request = false;
//                return "Error";
//        }
//        
//        loop_count++;
//        
//    } while(loop_request);
//    
//    ssh_set_blocking(_session, 1);
//    
//    nbytes = ssh_channel_read(channel, buffer, sizeof(buffer), 0);
//    
//    
//    std::string rtrnString = "";
//    
//    while (nbytes > 0)
//    {
//        std::string msg(buffer, nbytes);
//        
//        rtrnString += msg;
//        
//        nbytes = ssh_channel_read(channel, buffer, sizeof(buffer), 0);
//    }
//    
//    if (nbytes < 0)
//    {
////        ssh_channel_send_eof(channel);
////        ssh_channel_free(channel);
//        ssh_channel_close(channel);
//        return "Error";
//    }
//    
////    ssh_channel_send_eof(channel);
////    ssh_channel_free(channel);
//    ssh_channel_close(channel);
//    
//    return rtrnString;
//}
