#ifndef __MODEL_JSON_H__
#define __MODEL_JSON_H__

const char recognition_model_string_json[] = {"{\"NumModels\":1,\"ModelIndexes\":{\"0\":\"P_12_RANK_2\"},\"ModelDescriptions\":[{\"Name\":\"P_12_RANK_2\",\"ClassMaps\":{\"1\":\"CoffeeBrandA\",\"2\":\"CoffeeBrandB\",\"3\":\"CoffeeBrandC\",\"0\":\"Unknown\"},\"ModelType\":\"DecisionTreeEnsemble\",\"FeatureFunctions\":[\"Maximum\",\"AbsoluteMean\",\"NegativeZeroCrossings\",\"25thPercentile\"]}]}"};

int32_t recognition_model_string_json_len = sizeof(recognition_model_string_json);

#endif /* __MODEL_JSON_H__ */
