/**
 * @file        Eng_FeatureType.h
 * @brief       This is the Device Status ID Header file.
 *
 * <b> Copyright 2024 by Neurodyne Inc. All rights reserved.</b>
 *
 * This software is the confidential and proprietary information
 * of Neurodyne Inc. ("Confidential Information"). \n
 * You shall not disclose such Confidential Information and shall use
 * it only in accordance with the terms of the license agreement
 * you entered into with Samsung.
 *
 * @author		Jeongseob Kim
 * @imp			Jeongseob Kim
 * @dept		S/W R&D Group / Digital Printing Division
 * @date		25/02/2009(D/M/Y)
 * @version		V0.1
 */

#ifndef __ENG_FEATURETYPE_H__
#define __ENG_FEATURETYPE_H__

#define FEATURE_GET_INDEX(id)		(id & 0x00FFFFFF)				/* To get FEATURE ID  */
#define FEATURE_GET_SOURCE(id)		((id & 0xFF000000) >> 24)		/* To get FEATURE Source */

/**
 * Engine Feature Source
 */
#define ENGSM_FEATURE			0x01							/* EngSystemMgr */
#define ENGMH_FEATURE			0x02							/* EngController */
#define ENGEH_FEATURE			0x04							/* EngErrorHnd */
#define ENGSVC_FEATURE			0x08							/* EngIFSvc */

/**
 * Engine System Manager Feature ID Definition
 */
#define ENGSM_GET_MANAGER							0x01000010 
#define ENGSM_FEATURE_FASTFPOT						0x01000020
#define ENGSM_FEATURE_SLEEP2PRINT					0x01000030
#define	ENGSM_FEATURE_POWER							0x01000040
#define	ENGSM_FEATURE_MICOM							0x01000050


/**
 * Engine Motion Handler Feature ID Definition
 */

#define	ENGMH_HANDLER								0x02000000
#define	ENGMH_FEATURE_BALANCING						0x02000001
#define	ENGPH_FEATURE_WATCHING						0x02000002

#define	ENGMH_FEATURE_MAX_COUNT						10


/**
 * Engine Error Handler Message ID Definition
 */
#define ENGEH_HANDLER								0x10000010	


/**
 * Engine Interface Service Message ID Definition
 */



#endif /* __ENG_FEATURETYPE_H__ */

