/******************************************************************************

 @file  mac_radio_tx.h

 @brief Describe the purpose and contents of the file.

 Group: WCS, LPC
 Target Device: cc13xx_cc26xx

 ******************************************************************************
 
 Copyright (c) 2006-2022, Texas Instruments Incorporated

 All rights reserved not granted herein.
 Limited License.

 Texas Instruments Incorporated grants a world-wide, royalty-free,
 non-exclusive license under copyrights and patents it now or hereafter
 owns or controls to make, have made, use, import, offer to sell and sell
 ("Utilize") this software subject to the terms herein. With respect to the
 foregoing patent license, such license is granted solely to the extent that
 any such patent is necessary to Utilize the software alone. The patent
 license shall not apply to any combinations which include this software,
 other than combinations with devices manufactured by or for TI ("TI
 Devices"). No hardware patent is licensed hereunder.

 Redistributions must preserve existing copyright notices and reproduce
 this license (including the above copyright notice and the disclaimer and
 (if applicable) source code license limitations below) in the documentation
 and/or other materials provided with the distribution.

 Redistribution and use in binary form, without modification, are permitted
 provided that the following conditions are met:

   * No reverse engineering, decompilation, or disassembly of this software
     is permitted with respect to any software provided in binary form.
   * Any redistribution and use are licensed by TI for use only with TI Devices.
   * Nothing shall obligate TI to provide you with source code for the software
     licensed and provided to you in object code.

 If software source code is provided to you, modification and redistribution
 of the source code are permitted provided that the following conditions are
 met:

   * Any redistribution and use of the source code, including any resulting
     derivative works, are licensed by TI for use only with TI Devices.
   * Any redistribution and use of any object code compiled from the source
     code and any resulting derivative works, are licensed by TI for use
     only with TI Devices.

 Neither the name of Texas Instruments Incorporated nor the names of its
 suppliers may be used to endorse or promote products derived from this
 software without specific prior written permission.

 DISCLAIMER.

 THIS SOFTWARE IS PROVIDED BY TI AND TI'S LICENSORS "AS IS" AND ANY EXPRESS
 OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 IN NO EVENT SHALL TI AND TI'S LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

 ******************************************************************************
 
 
 *****************************************************************************/

#ifndef MAC_RADIO_TX_H
#define MAC_RADIO_TX_H

/* ------------------------------------------------------------------------------------------------
 *                                          Includes
 * ------------------------------------------------------------------------------------------------
 */
#include "hal_mcu.h"
#include "mac_mcu.h"
#include "mac_high_level.h"
#include "mac_timer.h"

// TODO: Figure out proper #include
#include "rf_mac_api.h"

extern RF_CmdHandle txCmdHandle;
extern RF_EventMask txCbEventMask;

/* ------------------------------------------------------------------------------------------------
 *                                           Typedefs
 * ------------------------------------------------------------------------------------------------
 */

/* Timer to trigger ACK transmission after turnaround time */
typedef struct
{
  macTimer_t      ackTimer;           /* ACK timer */
  macTimer_t      ackTimeout;         /* ACK timeout timer */
} macAckTimer_t;

/* ------------------------------------------------------------------------------------------------
 *                                   Global Variable Externs
 * ------------------------------------------------------------------------------------------------
 */

extern macAckTimer_t macAckTimer;
extern uint32_t      backoffBoundary;

/* ------------------------------------------------------------------------------------------------
 *                                         Prototypes
 * ------------------------------------------------------------------------------------------------
 */
MAC_INTERNAL_API void macRadioTxReset(void);

MAC_INTERNAL_API void macRadioTxPrepCsmaUnslotted(void);
MAC_INTERNAL_API void macRadioTxPrepCsmaSlotted(void);
MAC_INTERNAL_API void macRadioTxPrepSlotted(void);
MAC_INTERNAL_API void macRadioTxPrepLbt(uint8 state);

MAC_INTERNAL_API void macRadioTxGo(uint8 txType);
MAC_INTERNAL_API bool macRadioTxGoSlottedCsma(void);
MAC_INTERNAL_API void macRadioTxGoSlotted(void);
MAC_INTERNAL_API bool macRadioTxGoLbt(void);
MAC_INTERNAL_API void macRadioTxPrepGreenPower(void);
MAC_INTERNAL_API void macRadioTxGoGreenPower(void);

extern void macRadioTxRequestAckTimeout(void);
extern void macRadioTxCancelAckTimeout(void);
extern void macRadioTxRequestTxAck(void);
extern void macRadioTxCancelTxAck(void);
extern void macRadioSendImmAck(uint8 seq, uint8 panding);
extern void macRadioSendEnhAck(uint8 pending, sAddr_t *pDstAddr, ApiMac_sec_t *sec);
extern void macRadioCsmaTxCb(RF_Handle h, RF_CmdHandle ch, RF_EventMask e);
extern void macRadioLbtTxCb(RF_Handle h, RF_CmdHandle ch, RF_EventMask e);

#if defined (FEATURE_BEACON_MODE)
extern uint32 macRadioTxBOBoundary(void);
extern uint32 macRadioTxBackoffBoundary(uint32 backoffs);
#endif
/**************************************************************************************************
 */
#endif
