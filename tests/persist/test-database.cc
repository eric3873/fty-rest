#include <catch.hpp>
#include <tntdb/connect.h>
#include <tntdb/error.h>
#include <tntdb/result.h>
#include <tntdb/row.h>
#include <tntdb/value.h>

#include "dbpath.h"
#include "persistencelogic.h"
#include "nmap_msg.h"

TEST_CASE (
"nmap_msg_process",
"[db][database][store][storing][message][nmap][network][discovery]") {

    SECTION ("Send valid message to store.\n") {
        //
        // 13.11.2014: At the moment storing of the nmap_msg list_scan
        // requires only the 'addr' field to be filled in. Therefore
        // even a message that does not have all of the fields filled
        // in should be successfully stored.
        
        // First message
        const char *ip_1 = "10.130.38.197";
        const int state_1 = 0;
        const char *reason_1 = "echo-reply";
        nmap_msg_t *msg_1 = nmap_msg_new (NMAP_MSG_LIST_SCAN);
        assert (msg_1);

        nmap_msg_set_addr (msg_1, "%s", ip_1);
        nmap_msg_set_host_state (msg_1, (byte) state_1);
        nmap_msg_set_reason (msg_1, "%s", reason_1);

        REQUIRE_NOTHROW (persist::nmap_msg_process (url.c_str(), msg_1));

        // now check the db, this particular line has been stored.
        tntdb::Connection connection = tntdb::connectCached (url);
        tntdb::Statement st = connection.prepare(
            "SELECT COUNT(*) FROM t_bios_discovered_ip WHERE ip = ':v1'");
        tntdb::Result result = st.setString("v1", ip_1).select();
        REQUIRE (result.size() != 0);

        // Second message
        const char *ip_2 = "192.168.0.1";
        const int state_2 = 1;
 
        nmap_msg_t *msg_2 = nmap_msg_new (NMAP_MSG_LIST_SCAN);
        assert (msg_2);

        nmap_msg_set_addr (msg_2, "%s", ip_2);
        nmap_msg_set_host_state (msg_2, (byte) state_2);

        REQUIRE_NOTHROW (persist::nmap_msg_process (url.c_str(), msg_2));

        // now check the db, this particular line has been stored.
        // tntdb::Connection connection = tntdb::connectCached (url);

        result = st.setString("v1", ip_2).select();
        REQUIRE (result.size() != 0);

        // Third message
        



    } // SECTION 
}


