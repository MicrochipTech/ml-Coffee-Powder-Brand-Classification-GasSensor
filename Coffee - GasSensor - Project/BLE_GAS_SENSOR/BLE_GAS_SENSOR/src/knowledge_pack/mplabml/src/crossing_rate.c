
/*******************************************************************************
* Copyright (C) 2023 Microchip Technology Inc. and its subsidiaries.
*
* Subject to your compliance with these terms, you may use Microchip software
* and any derivatives exclusively with Microchip products. It is your
* responsibility to comply with third party license terms applicable to your
* use of third party software (including open source software) that may
* accompany Microchip software.
*
* THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
* EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
* WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
* PARTICULAR PURPOSE.
*
* IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
* INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
* WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
* BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
* FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
* ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
* THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *******************************************************************************/

#include "kbutils.h"
/*
 * crossing_rate
 *    Original version in KB transcode
 */
FLOAT crossing_rate(ringb *rb, int32_t base_index, int32_t num_rows, FLOAT threshold)
{
	int32_t ncrossings;
	int32_t int_threshold;

	int_threshold = (int32_t) threshold;
	ncrossings = utils_model_crossing_rate(rb, base_index, num_rows, int_threshold, 0, CROSSING_RATE);
	
	float f = (FLOAT)ncrossings / num_rows;

	if (!num_rows)
		return 0.0f;
	else
		return f;
}

/*
 * crossing_rate_over_zero
 *    Added for zero crossing optimization
 */
FLOAT crossing_rate_over_zero(ringb *rb, int32_t base_index, int32_t num_rows)
{
	// return right away if num_rows is 0
	if (!num_rows)
	{
		// should print out error: unexpected num_rows = 0 here!

		return 0.0f;
	}
	int32_t ncrossings = utils_model_crossing_rate(rb, base_index, num_rows, 0, 0, CROSSING_RATE_OVER_ZERO);

	return ((FLOAT)ncrossings / num_rows);
}

/*
 * crossing_rate_over_sum
 *    Added for mean crossing optimization
 */
FLOAT crossing_rate_over_sum(ringb *rb, int32_t base_index, int32_t num_rows, int32_t sum)
{
#if SML_DEBUG
	// return right away if num_rows is 0
	if (!num_rows)
	{
		// should print out error: unexpected num_rows = 0 here!
		return 0.0f;
	}
#endif //SML_DEBUG

	int32_t ncrossings = utils_model_crossing_rate(rb, base_index, num_rows, sum, 0, CROSSING_RATE_OVER_SUM);

	return ((FLOAT)ncrossings) / num_rows;
}

int32_t number_of_crossings_over_threshold(ringb *rb, int32_t base_index, int32_t num_rows, int32_t threshold)
{
	return utils_model_crossing_rate(rb, base_index, num_rows, threshold, 0, NUMBER_OF_CROSSINGS_OVER_THRESHOLD);
}

int32_t number_of_positive_crossings_over_threshold(ringb *rb, int32_t base_index, int32_t num_rows, int32_t threshold)
{
	return utils_model_crossing_rate(rb, base_index, num_rows, threshold, 0, NUMBER_OF_POSITIVE_CROSSINGS_OVER_THRESHOLD);
}

int32_t number_of_negative_crossings_over_threshold(ringb *rb, int32_t base_index, int32_t num_rows, int32_t threshold)
{
	return utils_model_crossing_rate(rb, base_index, num_rows, threshold, 0, NUMBER_OF_NEGATIVE_CROSSINGS_OVER_THRESHOLD);
}

int32_t number_of_crossings_over_threshold_regions(ringb *rb, int32_t base_index, int32_t num_rows, int32_t positive_threshold, int32_t negative_threshold)
{
	return utils_model_crossing_rate(rb, base_index, num_rows, positive_threshold, negative_threshold, NUMBER_OF_CROSSINGS_OVER_THRESHOLD_REGIONS);
}

int32_t number_of_positive_crossings_over_threshold_regions(ringb *rb, int32_t base_index, int32_t num_rows, int32_t positive_threshold, int32_t negative_threshold)
{
	return utils_model_crossing_rate(rb, base_index, num_rows, positive_threshold, negative_threshold, NUMBER_OF_POSITIVE_CROSSINGS_OVER_THRESHOLD_REGIONS);
}

int32_t number_of_negative_crossings_over_threshold_regions(ringb *rb, int32_t base_index, int32_t num_rows, int32_t positive_threshold, int32_t negative_threshold)
{
	return utils_model_crossing_rate(rb, base_index, num_rows, positive_threshold, negative_threshold, NUMBER_OF_NEGATIVE_CROSSINGS_OVER_THRESHOLD_REGIONS);
}