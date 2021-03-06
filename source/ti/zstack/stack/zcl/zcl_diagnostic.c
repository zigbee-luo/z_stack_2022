/**************************************************************************************************
  Filename:       zcl_diagnostic.c
  Revised:        $Date: 2014-03-13 15:57:20 -0700 (Thu, 13 Mar 2014) $
  Revision:       $Revision: 37682 $

  Description:    Zigbee Cluster Library - Diagnostics.


  Copyright (c) 2019, Texas Instruments Incorporated
  All rights reserved.

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions
  are met:

  *  Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.

  *  Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.

  *  Neither the name of Texas Instruments Incorporated nor the names of
      its contributors may be used to endorse or promote products derived
      from this software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
  PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
  PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
  OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
  WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
  OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**************************************************************************************************/

#ifdef ZCL_DIAGNOSTIC

/*********************************************************************
 * INCLUDES
 */
#include "zcl_diagnostic.h"
#include "zdiags.h"

#if !defined ( FEATURE_SYSTEM_STATS )
#error "ERROR: FEATURE_SYSTEM_STATS shall be defined if ZCL_DIAGNOSTICS is defined."
#endif

/*********************************************************************
 * MACROS
 */

/*********************************************************************
 * CONSTANTS
 */

/*********************************************************************
 * TYPEDEFS
 */
// Attribute record
typedef struct
{
  uint16_t  zclAttrId;        // Attribute ID as defined by ZCL Diagnostics Cluster
  uint8_t   dataType;         // Data Type - defined in af.h
  uint16_t  ZDiagsAttrId;     // Attribute ID as defined by ZDiags module
} zclDiagnosticAttr_t;



/*********************************************************************
 * GLOBAL VARIABLES
 */
CONST zclDiagnosticAttr_t zclDiagsAttrTable[] =
{
  {
    ATTRID_DIAGNOSTIC_NUMBER_OF_RESETS,
    ZCL_DATATYPE_UINT16,
    ZDIAGS_NUMBER_OF_RESETS
  },
  {
    ATTRID_DIAGNOSTIC_PERSISTENT_MEMORY_WRITES,
    ZCL_DATATYPE_UINT16,
    ZDIAGS_PERSISTENT_MEMORY_WRITES
  },
  {
    ATTRID_DIAGNOSTIC_MAC_RX_BCAST,
    ZCL_DATATYPE_UINT32,
    ZDIAGS_MAC_RX_BCAST
  },
  {
    ATTRID_DIAGNOSTIC_MAC_TX_BCAST,
    ZCL_DATATYPE_UINT32,
    ZDIAGS_MAC_TX_BCAST
  },
  {
    ATTRID_DIAGNOSTIC_MAC_RX_UCAST,
    ZCL_DATATYPE_UINT32,
    ZDIAGS_MAC_RX_UCAST
  },
  {
    ATTRID_DIAGNOSTIC_MAC_TX_UCAST,
    ZCL_DATATYPE_UINT32,
    ZDIAGS_MAC_TX_UCAST
  },
  {
    ATTRID_DIAGNOSTIC_MAC_TX_UCAST_RETRY,
    ZCL_DATATYPE_UINT16,
    ZDIAGS_MAC_TX_UCAST_RETRY
  },
  {
    ATTRID_DIAGNOSTIC_MAC_TX_UCAST_FAIL,
    ZCL_DATATYPE_UINT16,
    ZDIAGS_MAC_TX_UCAST_FAIL
  },
  {
    ATTRID_DIAGNOSTIC_APS_RX_BCAST,
    ZCL_DATATYPE_UINT16,
    ZDIAGS_APS_RX_BCAST
  },
  {
    ATTRID_DIAGNOSTIC_APS_TX_BCAST,
    ZCL_DATATYPE_UINT16,
    ZDIAGS_APS_TX_BCAST
  },
  {
    ATTRID_DIAGNOSTIC_APS_RX_UCAST,
    ZCL_DATATYPE_UINT16,
    ZDIAGS_APS_RX_UCAST
  },
  {
    ATTRID_DIAGNOSTIC_APS_TX_UCAST_SUCCESS,
    ZCL_DATATYPE_UINT16,
    ZDIAGS_APS_TX_UCAST_SUCCESS
  },
  {
    ATTRID_DIAGNOSTIC_APS_TX_UCAST_RETRY,
    ZCL_DATATYPE_UINT16,
    ZDIAGS_APS_TX_UCAST_RETRY
  },
  {
    ATTRID_DIAGNOSTIC_APS_TX_UCAST_FAIL,
    ZCL_DATATYPE_UINT16,
    ZDIAGS_APS_TX_UCAST_FAIL
  },
  {
    ATTRID_DIAGNOSTIC_ROUTE_DISC_INITIATED,
    ZCL_DATATYPE_UINT16,
    ZDIAGS_ROUTE_DISC_INITIATED
  },
  {
    ATTRID_DIAGNOSTIC_NEIGHBOR_ADDED,
    ZCL_DATATYPE_UINT16,
    ZDIAGS_NEIGHBOR_ADDED
  },
  {
    ATTRID_DIAGNOSTIC_NEIGHBOR_REMOVED,
    ZCL_DATATYPE_UINT16,
    ZDIAGS_NEIGHBOR_REMOVED
  },
  {
    ATTRID_DIAGNOSTIC_NEIGHBOR_STALE,
    ZCL_DATATYPE_UINT16,
    ZDIAGS_NEIGHBOR_STALE
  },
  {
    ATTRID_DIAGNOSTIC_JOIN_INDICATION,
    ZCL_DATATYPE_UINT16,
    ZDIAGS_JOIN_INDICATION
  },
  {
    ATTRID_DIAGNOSTIC_CHILD_MOVED,
    ZCL_DATATYPE_UINT16,
    ZDIAGS_CHILD_MOVED
  },
  {
    ATTRID_DIAGNOSTIC_NWK_FC_FAILURE,
    ZCL_DATATYPE_UINT16,
    ZDIAGS_NWK_FC_FAILURE
  },
  {
    ATTRID_DIAGNOSTIC_APS_FC_FAILURE,
    ZCL_DATATYPE_UINT16,
    ZDIAGS_APS_FC_FAILURE
  },
  {
    ATTRID_DIAGNOSTIC_APS_UNAUTHORIZED_KEY,
    ZCL_DATATYPE_UINT16,
    ZDIAGS_APS_UNAUTHORIZED_KEY
  },
  {
    ATTRID_DIAGNOSTIC_NWK_DECRYPT_FAILURES,
    ZCL_DATATYPE_UINT16,
    ZDIAGS_NWK_DECRYPT_FAILURES
  },
  {
    ATTRID_DIAGNOSTIC_APS_DECRYPT_FAILURES,
    ZCL_DATATYPE_UINT16,
    ZDIAGS_APS_DECRYPT_FAILURES
  },
  {
    ATTRID_DIAGNOSTIC_PACKET_BUFFER_ALLOCATE_FAILURES,
    ZCL_DATATYPE_UINT16,
    ZDIAGS_PACKET_BUFFER_ALLOCATE_FAILURES
  },
  {
    ATTRID_DIAGNOSTIC_RELAYED_UCAST,
    ZCL_DATATYPE_UINT16,
    ZDIAGS_RELAYED_UCAST
  },
  {
    ATTRID_DIAGNOSTIC_PHY_TO_MAC_QUEUE_LIMIT_REACHED,
    ZCL_DATATYPE_UINT16,
    ZDIAGS_PHY_TO_MAC_QUEUE_LIMIT_REACHED
  },
  {
    ATTRID_DIAGNOSTIC_PACKET_VALIDATE_DROP_COUNT,
    ZCL_DATATYPE_UINT16,
    ZDIAGS_PACKET_VALIDATE_DROP_COUNT
  },
};

/*********************************************************************
 * LOCAL VARIABLES
 */

/*********************************************************************
 * LOCAL FUNCTIONS
 */
static ZStatus_t zclDiagnostic_GetAttribData( uint16_t zclAttrId, uint16_t *zdiagsAttrId, uint16_t *dataLen );

/****************************************************************************
 * @fn          zclDiagnostic_GetAttribData()
 *
 * @brief       Gets the Z-Stack attribute data for a specific ZCL Diagnostics
 *              AttributeID.
 *
 * @param       none.
 *
 * @return      none.
 */
static ZStatus_t zclDiagnostic_GetAttribData( uint16_t zclAttrId, uint16_t *zdiagsAttrId, uint16_t *dataLen )
{
  uint8_t i;
  uint8_t attrTableSize = sizeof(zclDiagsAttrTable);

  for ( i = 0; i < attrTableSize; i++ )
  {
    if ( zclDiagsAttrTable[i].zclAttrId == zclAttrId )
    {
      *zdiagsAttrId = zclDiagsAttrTable[i].ZDiagsAttrId;
      *dataLen = (uint16_t)zclGetDataTypeLength( zclDiagsAttrTable[i].dataType );

      return ( ZSuccess );
    }
  }

  return ( ZFailure );
}

/****************************************************************************
 * @fn          zclDiagnostic_InitStats()
 *
 * @brief       Initialize the statistics table.
 *
 * @param       none.
 *
 * @return      ZSuccess - if NV data was initialized successfully.
 *              ZFailure - Otherwise
 */
uint8_t zclDiagnostic_InitStats( void )
{
  // Initialize the Diagnostics table in the Lower layer
  return ( ZDiagsInitStats() );
}

/****************************************************************************
 * @fn          zclDiagnostic_ClearStats
 *
 * @brief       Clears the statistics table in RAM and NV if option flag set.
 *
 * @param       clearNV   - Option flag to clear NV data.
 *
 * @return      System Clock.
 */
uint32_t zclDiagnostic_ClearStats( bool clearNV )
{
  // calls the diagnostics function to clear statistics and returns the system clock
  return ZDiagsClearStats( clearNV );
}

/****************************************************************************
 * @fn          zclDiagnostic_GetStatsAttr
 *
 * @brief       Reads Diagnostic values based on specific ZCL Diagnostics
 *              attribute ID
 *
 * @param       attributeId  input  - ZCL identifier for the required attribute
 * @param       value       output - value of the specific item
 *
 * NOTE:  the user of this function will have to cast the value
 *        based on the type of the attributeId, the returned value
 *        will allways be uint32_t
 *
 * @return      ZStatus_t
 */
ZStatus_t zclDiagnostic_GetStatsAttr( uint16_t attributeId, uint32_t *attrValue, uint16_t *dataLen )
{
  uint8_t status = ZSuccess;
  uint16_t ZDiagsAttrId;

  // this atribute is a calculated value
  if ( attributeId == ATTRID_DIAGNOSTIC_AVERAGE_MAC_RETRY_PER_APS_MESSAGE_SENT )
  {
    uint32_t macRetriesPerApsTx;
    uint32_t apsTxUcastSuccess;
    uint32_t apsTxUcastFailure;

    // retrieve each attribute to calculate the requested value
    macRetriesPerApsTx = ZDiagsGetStatsAttr( ZDIAGS_MAC_RETRIES_PER_APS_TX_SUCCESS );

    apsTxUcastSuccess = ZDiagsGetStatsAttr( ZDIAGS_APS_TX_UCAST_SUCCESS );

    apsTxUcastFailure = ZDiagsGetStatsAttr( ZDIAGS_APS_TX_UCAST_FAIL );

    *dataLen = 2;  // this is the lenght of ATTRID_DIAGNOSTIC_AVERAGE_MAC_RETRY_PER_APS_MESSAGE_SENT

    if ( ( apsTxUcastSuccess != 0 ) || ( apsTxUcastFailure != 0 ) )
    {
      // This formula considers the total MAC Failures per APS transmitted packet.
      // If MAC PIB element maxFrameRetries is changed from the default value 3, this formula
      // shall be updated and replace 4 with (MAC PIB maxFrameRetries+1) value
      *attrValue = ( macRetriesPerApsTx + ( apsTxUcastFailure * 4 ) ) / ( apsTxUcastSuccess + apsTxUcastFailure );
    }
    else
    {
      *attrValue = 0;
    }
  }
  // look-up for ZDiags attribute ID, based on the ZCL Diagnostics cluster attribute ID
  else if ( zclDiagnostic_GetAttribData( attributeId, &ZDiagsAttrId, dataLen ) == ZSuccess )
  {
    *attrValue = ZDiagsGetStatsAttr( ZDiagsAttrId );
  }
  else
  {
    status = ZFailure;
  }

  return ( status );
}

/*********************************************************************
 * @fn      zclDiagnostic_ReadWriteAttrCB
 *
 * @brief   Handle Diagnostics attributes.
 *
 * @param   endpoint - Application's endpoint, fixed by luoyiming 2020-01-07
 * @param   pAttr - pointer to attributes, fixed by luoyiming 2020-01-07
 * @param   oper - ZCL_OPER_LEN, ZCL_OPER_READ, or ZCL_OPER_WRITE
 * @param   pValue - pointer to attribute value, OTA endian
 * @param   pLen - length of attribute value read, native endian
 *
 * @return  status
 */
ZStatus_t zclDiagnostic_ReadWriteAttrCB( uint8_t endpoint, zclAttrRec_t *pAttr, uint8_t oper,
                                         uint8_t *pValue, uint16_t *pLen )
{
  ZStatus_t status = ZSuccess;
  uint16_t tempAttr;
  uint32_t attrValue;
  afIncomingMSGPacket_t *origPkt;
  uint16_t attrId = pAttr->attr.attrId; // add by luoyiming 2020-01-07

  origPkt = zcl_getRawAFMsg();

  switch ( oper )
  {
    case ZCL_OPER_LEN:
      if ( ( attrId == ATTRID_DIAGNOSTIC_LAST_MESSAGE_LQI ) ||
           ( attrId == ATTRID_DIAGNOSTIC_LAST_MESSAGE_RSSI ) )
      {
        *pLen = 1;
      }
      else if ( attrId == ATTRID_DIAGNOSTIC_AVERAGE_MAC_RETRY_PER_APS_MESSAGE_SENT )
      {
        *pLen = 2;
      }
      // The next function call only returns the length for attributes that are defined
      // in lower layers
      else if ( zclDiagnostic_GetAttribData( attrId, &tempAttr, pLen ) != ZSuccess )
      {
        *pLen = 0;
        status = ZFailure;  // invalid length
      }
      break;

    case ZCL_OPER_READ:
      // Identify if incoming msg is LQI or RSSI attribute
      // and return the LQI and RSSI of the incoming values
      if ( attrId == ATTRID_DIAGNOSTIC_LAST_MESSAGE_LQI )
      {
        *pLen = 1;
        attrValue = origPkt->LinkQuality;
      }
      else if ( attrId == ATTRID_DIAGNOSTIC_LAST_MESSAGE_RSSI )
      {
        //origPkt = zcl_getRawAFMsg();
        *pLen = 1;
        attrValue = origPkt->rssi;
      }
      else if ( zclDiagnostic_GetStatsAttr( attrId, &attrValue, pLen ) == ZSuccess )
      {
        if ( ( attrId == ATTRID_DIAGNOSTIC_MAC_TX_UCAST_RETRY ) ||
             ( attrId == ATTRID_DIAGNOSTIC_MAC_TX_UCAST_FAIL  ) )
        {
          // The lower layer counter is a 32 bit counter, report the higher 16 bit value
          // util the lower layer counter wraps-up
          if ( attrValue > 0x0000FFFF )
          {
            attrValue = 0x0000FFFF;
          }
        }
      }
      else
      {
        *pLen = 0;
        status = ZFailure;  // invalid attribute
      }

      if ( *pLen == 1 )
      {
        pValue[0] = BREAK_UINT32( attrValue, 0 );
      }
      else if ( *pLen == 2 )
      {
        pValue[0] = LO_UINT16( attrValue );
        pValue[1] = HI_UINT16( attrValue );
      }
      else if ( *pLen == 4 )
      {
        pValue[0] = BREAK_UINT32( attrValue, 0 );
        pValue[1] = BREAK_UINT32( attrValue, 1 );
        pValue[2] = BREAK_UINT32( attrValue, 2 );
        pValue[3] = BREAK_UINT32( attrValue, 3 );
      }

      break;

    case ZCL_OPER_WRITE:
      status = ZFailure;  // All attributes in Diagnostics cluster are READ ONLY
      break;
  }

  return ( status );
}

/****************************************************************************
 * @fn          zclDiagnostic_RestoreStatsFromNV
 *
 * @brief       Restores the statistics table from NV into the RAM table.
 *
 * @param       none.
 *
 * @return      ZSuccess - if NV data was restored from NV.
 *              ZFailure - Otherwise, NV_OPER_FAILED for failure.
 */
uint8_t zclDiagnostic_RestoreStatsFromNV( void )
{
  return ( ZDiagsRestoreStatsFromNV() );
}

   /****************************************************************************
 * @fn          zclDiagnostic_SaveStatsToNV
 *
 * @brief       Saves the statistics table from RAM to NV.
 *
 * @param       none.
 *
 * @return      System Time.
 */
uint32_t zclDiagnostic_SaveStatsToNV( void )
{
   return( ZDiagsSaveStatsToNV() );
}


#endif // ZCL_DIAGNOSTIC
/********************************************************************************************
*********************************************************************************************/

