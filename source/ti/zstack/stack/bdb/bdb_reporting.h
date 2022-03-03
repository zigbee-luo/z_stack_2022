/**************************************************************************************************
  Filename:       bdb_reporting.h
  Revised:        $Date: 2016-07-04 10:15:00 -0800 (Mon, 4 Jul 2016) $
  Revision:       $Revision: - $

  Description:    This file contains the definitions used for the Bdb attribute
                  reporting.


  Copyright 2006-2014 Texas Instruments Incorporated.

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
**************************************************************************************************/

#ifndef BDB_REPORTING_H
#define BDB_REPORTING_H

#ifdef BDB_REPORTING

#include "zcl.h"

/*********************************************************************
 * CONSTANTS
 */

// Errors, boolean and reporting constants definitions used in the bdb reporting code
#define BDBREPORTING_FALSE 0
#define BDBREPORTING_TRUE 1
#define BDBREPORTING_ERROR 1
#define BDBREPORTING_IGNORE 0xFF
#define BDBREPORTING_OUTOFMEMORYERROR 2
#define BDBREPORTING_SUCCESS 0
#define BDBREPORTING_INVALIDINDEX 0xFF

#define BDBREPORTING_DIRECRION_SEVER   ZCL_FRAME_CLIENT_SERVER_DIR // fixed by luoyiming 2021-05-31
#define BDBREPORTING_DIRECRION_CLIENT  ZCL_FRAME_SERVER_CLIENT_DIR // fixed by luoyiming 2021-05-31

/*********************************************************************
 * TYPEDEFS
 */


/*********************************************************************
 * GLOBAL VARIABLES
 */

/*
 * @fn      pBdb_SendReportCmdCallback
 *
 * @brief   Customer send report command callback. If had set this callback,bdb
 *          won't send report command
 * 
 * @param   dstAddr - destination address
 * @param   clusterID - cluster ID
 * @param   reportCmd - report command to be sent
 * @param   direction - direction of the command
 * @param   manuCode - manufacturer code for proprietary extensions to a profile
 * @param   seqNum - transaction sequence number
 * @param   isReqFromApp - Indicates where it comes from application thread or stack thread 
 *
 * @return  if false, send reporting in stack task, fixed by luoyiming 2019-11-22
 *
*/
extern bool (*pBdb_SendReportCmdCallback)( uint8_t srcEP, afAddrType_t *dstAddr, uint16_t clusterID,
                                           zclReportCmd_t *reportCmd, uint8_t direction, uint8_t disableDefaultRsp,
                                           uint16_t manuCode, uint8_t seqNum );

/*********************************************************************
 * FUNCTIONS
 */

void bdb_RepInit( void );
void bdb_RepConstructReportingData( void );
void bdb_RepProcessEvent( void );
void bdb_RepStartOrContinueReporting( void );
void bdb_RepMarkHasBindingInEndpointClusterArray( uint8_t endpoint, uint16_t cluster, uint16_t manuCode,
                                                  uint8_t direction, uint8_t unMark, uint8_t setNoNextIncrementFlag );
ZStatus_t bdb_ProcessInConfigReportCmd( zclIncomingMsg_t *pInMsg );
ZStatus_t bdb_ProcessInReadReportCfgCmd( zclIncomingMsg_t *pInMsg );
void bdb_RepUpdateMarkBindings( void );

#endif //BDB_REPORTING
#endif /* BDB_REPORTING_H */

