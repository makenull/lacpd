/*
 * Copyright (C) 2005-2015 Hewlett-Packard Development Company, L.P.
 * All Rights Reserved.
 *
 *   Licensed under the Apache License, Version 2.0 (the "License"); you may
 *   not use this file except in compliance with the License. You may obtain
 *   a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 *   Unless required by applicable law or agreed to in writing, software
 *   distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 *   WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
 *   License for the specific language governing permissions and limitations
 *   under the License.
 */

/*----------------------------------------------------------------------
 *  MODULE:
 *
 *     lacp_support.h
 *
 *  SUB-SYSTEM:
 *
 *  ABSTRACT
 *     The file contains the Global function declarations,
 *     global variables' extern declarations and other misc. macors.
 *  AUTHOR:
 *
 *    Gowrishankar, Riverstone Networks
 *
 *  CREATION DATE:
 *
 *    March 5, 2000
 *
 *
 *----------------------------------------------------------------------*/

#ifndef _LACP_SUPPORT_H_
#define _LACP_SUPPORT_H_

#include "lacp.h"

/*****************************************************************************
 *   MISC. MACROS (to be placed in appropriate h files later)
 *****************************************************************************/
#define TIMER_NAME_STRING_LENGTH 64
#define LACP_PERIODIC_TX_TIMER_TEGBIT 1
#define LACP_RECEIVE_TIMER_TEGBIT 2
#define LACP_RECV_Q_TEGBIT 0

/*****************************************************************************
 *   Some of these have been moved to include/nemo/lacp/lacp_cmn.h
 *****************************************************************************/
// #define LACP_ACTIVE_MODE 1
// #define LACP_PASSIVE_MODE 0

/* Time macros */
// #define SHORT_TIMEOUT 1
// #define LONG_TIMEOUT  0
#if 0
#define FAST_PERIODIC_TIME NU_ONESEC        /* 1 second */
#define SLOW_PERIODIC_TIME (30 * NU_ONESEC) /* 30 seconds */
#define SHORT_TIMEOUT_TIME (3 * FAST_PERIODIC_TIME)  /* 3 seconds */
#define LONG_TIMEOUT_TIME  (3 * SLOW_PERIODIC_TIME)  /* 90 seconds */
#define AGGREGATE_WAIT_TIME (2 * NU_ONESEC)  /* 2 seconds */
#endif
#define FAST_PERIODIC_COUNT 1                          /* 1 second */
#define SLOW_PERIODIC_COUNT 30                         /* 30 seconds */
#define SHORT_TIMEOUT_COUNT (3 * FAST_PERIODIC_COUNT)  /* 3 seconds */
#define LONG_TIMEOUT_COUNT  (3 * SLOW_PERIODIC_COUNT)  /* 90 seconds */
#define AGGREGATE_WAIT_COUNT 2                         /* 2 seconds */

#define LACP_MAX_KEY	((1 << 16) - 1)

/* Aggregation state/bit  */
// #define INDIVIDUAL 0
// #define AGGREGATABLE 1
// #define UNKNOWN 2

#define STATE_STRING_SIZE 32
#define DEAGGREGATION_DELAY_COUNT 3

#define CMD_PRESENT 0x55

#define MAX_ASYNC_TX 3

/*****************************************************************************
 *      DEFAULT VALUES 
 *****************************************************************************/
#define DEFAULT_PARTNER_PORT_NUMBER 0x0
#define DEFAULT_PARTNER_ADMIN_PORT_KEY 0x0
#define DEFAULT_PARTNER_ADMIN_PORT_PRIORITY 0x0
#define DEFAULT_PARTNER_ADMIN_SYSTEM_PRIORITY 0x0

#define DEFAULT_COLLECTOR_MAX_DELAY 1

/*****************************************************************************
 *      BIT FIELDS FOR PER PORT VARIABLES
 *****************************************************************************/
#define PORT_NUMBER_BIT 0x1
#define PORT_PRIORITY_BIT 0x2
#define PORT_KEY_BIT 0x4
#define PORT_STATE_LACP_ACTIVITY_BIT 0x8
#define PORT_STATE_LACP_TIMEOUT_BIT 0x10
#define PORT_STATE_AGGREGATION_BIT 0x20
#define PORT_STATE_SYNCHRONISATION_BIT 0x40
#define PORT_STATE_COLLECTING_BIT 0x80
#define PORT_STATE_DISTRIBUTING_BIT 0x100
#define PORT_STATE_DEFAULTED_BIT 0x200
#define PORT_STATE_EXPIRED_BIT 0x400
#define PORT_SYSTEM_MAC_ADDR_BIT 0x800
#define PORT_SYSTEM_PRIORITY_BIT 0x1000
#define ALL_PARAMS 0xFFFF

#define FOR_ALL_LAGS(i) for ((i) = 1; (i) <= MLS_MAXPORTS; (i)++)

/*****************************************************************************/
/*                   Prototypes for Global routines                          */
/*****************************************************************************/
void LACP_mux_fsm(int, int, lacp_per_port_variables_t *);
void LACP_periodic_tx_fsm(int, int, lacp_per_port_variables_t *);
void LACP_receive_fsm(int, 
                      int, 
                      lacpdu_payload_t *, 
                      lacp_per_port_variables_t *);
void LACP_transmit_lacpdu(lacp_per_port_variables_t *);
struct lacp_per_port_variables; // XXX
#if 0
void LACP_process_lacpdu(linkGroup_t *, 
                         struct lacp_per_port_variables *, 
                         void *);
void LACPAssignFunctions(linkGroup_t *);
void LACPAssignPortFunctions(cgPort_t *);
void LACP_initialize(linkGroup_t *);
#endif
/* XXX PI */
void LACP_process_lacpdu(struct lacp_per_port_variables *, 
                         void *);
void LACP_initialize_port(port_handle_t lport_handle,
                     short port_id,
                     unsigned long flags,
                     short port_key,
                     short port_priority,
                     short activity,
                     short timeout,
                     short aggregation,
                     int link_state,
                     int link_speed,
                     int hw_collecting);
void LACP_update_port_params(port_handle_t lport_handle,
                     unsigned long flags,
                     short data, int hw_collecting);
int port_number_2_link_group_index(int);
void LAG_selection(lacp_per_port_variables_t *);
void LAG_id_string(char *const, LAG_Id_t *const);
int loop_back_check(lacp_per_port_variables_t *);
void print_lacp_fsm_state(port_handle_t);
int Lacp_Get_Remote_Port(port_handle_t);
macaddr_3_t *Lacp_Get_Remote_Mac(port_handle_t);
void set_actor_admin_parms_2_oper(lacp_per_port_variables_t *, int);
void set_partner_admin_parms_2_oper(lacp_per_port_variables_t *, int);
void LACPResetProtocol(lacp_per_port_variables_t *);
void print_lacp_params(port_handle_t);
void print_lacp_stats(port_handle_t);
void print_lacp_lags(port_handle_t);
void print_lacp_key_group(const int);
void start_wait_while_timer(lacp_per_port_variables_t *);
#if 0
void print_lacp_aggregator(linkGroup_t *);
#endif
void periodic_tx_state_string(int, char *);
void mux_state_string(int, char *);
void rx_state_string(int, char *);
inline int lacp_lock(void); // XXX
inline void lacp_unlock(int);
void LACP_async_transmit_lacpdu(lacp_per_port_variables_t *);
void LACP_sync_transmit_lacpdu(lacp_per_port_variables_t *);
void display_lacpdu(lacpdu_payload_t *,char *, char *, int);
#if 0
inline aggregator_t *LACPGetAggregatorFromLinkId(const int);
inline LAG_t *LACPGetLagFromLinkGroup(const linkGroup_t *const);
#endif
void LAG_detach_aggregator(LAG_t *const);
void LACP_reset_port(port_handle_t);
int LACP_waiting_link_up(port_handle_t);
void LACP_poll_link_state(lacp_per_port_variables_t *);
void display_marker_response_pdu(marker_pdu_payload_t *, char *, char *, int);
void LACPPutPortUp(ulong);
void set_all_port_system_priority(void);

/*****************************************************************************
 *       Extern declarations for global variables
 *****************************************************************************/
// XXX extern lacp_per_port_variables_t lacp_per_port_vars_array[MLS_MAXPORTS+1];
extern nemo_avl_tree_t lacp_per_port_vars_tree;
// XXX extern NU_TIMER lacp_periodic_tx_timer;
// XXX extern NU_TIMER lacp_receive_timer;
extern const char lacp_mcast_addr[];
extern const char default_partner_system_mac[];
extern int lacp_tables_last_changed_time;
extern LAG_t *lacp_lags[];
extern unsigned int lacp_cli_opt_mask[];
extern void lacp_support_diag_dump(int port);

#endif  /* _LACP_SUPPORT_H_ */