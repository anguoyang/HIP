/*
Copyright (c) 2015 - present Advanced Micro Devices, Inc. All rights reserved.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

#include "CUDA2HIP.h"

// Maps the names of CUDA SPARSE API types to the corresponding HIP types
const std::map<llvm::StringRef, hipCounter> CUDA_SPARSE_TYPE_NAME_MAP{

  // 1. Structs
  {"cusparseContext",                           {"hipsparseContext",                           "", CONV_TYPE, API_SPARSE, HIP_UNSUPPORTED}},
  {"cusparseHandle_t",                          {"hipsparseHandle_t",                          "", CONV_TYPE, API_SPARSE}},

  {"cusparseHybMat",                            {"hipsparseHybMat",                            "", CONV_TYPE, API_SPARSE, HIP_UNSUPPORTED}},
  {"cusparseHybMat_t",                          {"hipsparseHybMat_t",                          "", CONV_TYPE, API_SPARSE}},

  {"cusparseMatDescr",                          {"hipsparseMatDescr",                          "", CONV_TYPE, API_SPARSE, HIP_UNSUPPORTED}},
  {"cusparseMatDescr_t",                        {"hipsparseMatDescr_t",                        "", CONV_TYPE, API_SPARSE}},

  {"cusparseSolveAnalysisInfo",                 {"hipsparseSolveAnalysisInfo",                 "", CONV_TYPE, API_SPARSE, HIP_UNSUPPORTED}},
  {"cusparseSolveAnalysisInfo_t",               {"hipsparseSolveAnalysisInfo_t",               "", CONV_TYPE, API_SPARSE, HIP_UNSUPPORTED}},

  {"csrsv2Info",                                {"csrsv2Info",                                 "", CONV_TYPE, API_SPARSE, HIP_UNSUPPORTED}},
  {"csrsv2Info_t",                              {"csrsv2Info_t",                               "", CONV_TYPE, API_SPARSE}},

  {"csrsm2Info",                                {"csrsm2Info",                                 "", CONV_TYPE, API_SPARSE, HIP_UNSUPPORTED}},
  {"csrsm2Info_t",                              {"csrsm2Info_t",                               "", CONV_TYPE, API_SPARSE, HIP_UNSUPPORTED}},

  {"bsrsv2Info",                                {"bsrsv2Info",                                 "", CONV_TYPE, API_SPARSE, HIP_UNSUPPORTED}},
  {"bsrsv2Info_t",                              {"bsrsv2Info_t",                               "", CONV_TYPE, API_SPARSE, HIP_UNSUPPORTED}},

  {"bsrsm2Info",                                {"bsrsm2Info",                                 "", CONV_TYPE, API_SPARSE, HIP_UNSUPPORTED}},
  {"bsrsm2Info_t",                              {"bsrsm2Info_t",                               "", CONV_TYPE, API_SPARSE, HIP_UNSUPPORTED}},

  {"bsric02Info",                               {"bsric02Info",                                "", CONV_TYPE, API_SPARSE, HIP_UNSUPPORTED}},
  {"bsric02Info_t",                             {"bsric02Info_t",                              "", CONV_TYPE, API_SPARSE, HIP_UNSUPPORTED}},

  {"csrilu02Info",                              {"csrilu02Info",                               "", CONV_TYPE, API_SPARSE, HIP_UNSUPPORTED}},
  {"csrilu02Info_t",                            {"csrilu02Info_t",                             "", CONV_TYPE, API_SPARSE}},

  {"bsrilu02Info",                              {"bsrilu02Info",                               "", CONV_TYPE, API_SPARSE, HIP_UNSUPPORTED}},
  {"bsrilu02Info_t",                            {"bsrilu02Info_t",                             "", CONV_TYPE, API_SPARSE, HIP_UNSUPPORTED}},

  {"csru2csrInfo",                              {"csru2csrInfo",                               "", CONV_TYPE, API_SPARSE, HIP_UNSUPPORTED}},
  {"csru2csrInfo_t",                            {"csru2csrInfo_t",                             "", CONV_TYPE, API_SPARSE, HIP_UNSUPPORTED}},

  {"csrgemm2Info",                              {"csrgemm2Info",                               "", CONV_TYPE, API_SPARSE}},
  {"csrgemm2Info_t",                            {"csrgemm2Info_t",                             "", CONV_TYPE, API_SPARSE}},

  {"cusparseColorInfo",                         {"hipsparseColorInfo",                         "", CONV_TYPE, API_SPARSE, HIP_UNSUPPORTED}},
  {"cusparseColorInfo_t",                       {"hipsparseColorInfo_t",                       "", CONV_TYPE, API_SPARSE, HIP_UNSUPPORTED}},

  {"pruneInfo",                                 {"pruneInfo",                                  "", CONV_TYPE, API_SPARSE, HIP_UNSUPPORTED}},
  {"pruneInfo_t",                               {"pruneInfo_t",                                "", CONV_TYPE, API_SPARSE, HIP_UNSUPPORTED}},

  {"cusparseSpMatDescr",                        {"hipsparseSpMatDescr",                        "", CONV_TYPE, API_SPARSE, HIP_UNSUPPORTED}},
  {"cusparseSpMatDescr_t",                      {"hipsparseSpMatDescr_t",                      "", CONV_TYPE, API_SPARSE, HIP_UNSUPPORTED}},

  {"cusparseDnMatDescr",                        {"hipsparseDnMatDescr",                        "", CONV_TYPE, API_SPARSE, HIP_UNSUPPORTED}},
  {"cusparseDnMatDescr_t",                      {"hipsparseDnMatDescr_t",                      "", CONV_TYPE, API_SPARSE, HIP_UNSUPPORTED}},

  {"cusparseSpVecDescr",                        {"hipsparseSpVecDescr",                        "", CONV_TYPE, API_SPARSE, HIP_UNSUPPORTED}},
  {"cusparseSpVecDescr_t",                      {"hipsparseSpVecDescr_t",                      "", CONV_TYPE, API_SPARSE, HIP_UNSUPPORTED}},

  {"cusparseDnVecDescr",                        {"hipsparseDnVecDescr",                        "", CONV_TYPE, API_SPARSE, HIP_UNSUPPORTED}},
  {"cusparseDnVecDescr_t",                      {"hipsparseDnVecDescr_t",                      "", CONV_TYPE, API_SPARSE, HIP_UNSUPPORTED}},

  // 2. Enums
  {"cusparseAction_t",                          {"hipsparseAction_t",                          "", CONV_TYPE, API_SPARSE}},
  {"CUSPARSE_ACTION_SYMBOLIC",                  {"HIPSPARSE_ACTION_SYMBOLIC",                  "", CONV_NUMERIC_LITERAL, API_SPARSE}},
  {"CUSPARSE_ACTION_NUMERIC",                   {"HIPSPARSE_ACTION_NUMERIC",                   "", CONV_NUMERIC_LITERAL, API_SPARSE}},

  {"cusparseDirection_t",                       {"hipsparseDirection_t",                       "", CONV_TYPE, API_SPARSE, HIP_UNSUPPORTED}},
  {"CUSPARSE_DIRECTION_ROW",                    {"HIPSPARSE_DIRECTION_ROW",                    "", CONV_NUMERIC_LITERAL, API_SPARSE, HIP_UNSUPPORTED}},
  {"CUSPARSE_DIRECTION_COLUMN",                 {"HIPSPARSE_DIRECTION_COLUMN",                 "", CONV_NUMERIC_LITERAL, API_SPARSE, HIP_UNSUPPORTED}},

  {"cusparseHybPartition_t",                    {"hipsparseHybPartition_t",                    "", CONV_TYPE, API_SPARSE}},
  {"CUSPARSE_HYB_PARTITION_AUTO",               {"HIPSPARSE_HYB_PARTITION_AUTO",               "", CONV_NUMERIC_LITERAL, API_SPARSE}},
  {"CUSPARSE_HYB_PARTITION_USER",               {"HIPSPARSE_HYB_PARTITION_USER",               "", CONV_NUMERIC_LITERAL, API_SPARSE}},
  {"CUSPARSE_HYB_PARTITION_MAX",                {"HIPSPARSE_HYB_PARTITION_MAX",                "", CONV_NUMERIC_LITERAL, API_SPARSE}},

  {"cusparseDiagType_t",                        {"hipsparseDiagType_t",                        "", CONV_TYPE, API_SPARSE}},
  {"CUSPARSE_DIAG_TYPE_NON_UNIT",               {"HIPSPARSE_DIAG_TYPE_NON_UNIT",               "", CONV_NUMERIC_LITERAL, API_SPARSE}},
  {"CUSPARSE_DIAG_TYPE_UNIT",                   {"HIPSPARSE_DIAG_TYPE_UNIT",                   "", CONV_NUMERIC_LITERAL, API_SPARSE}},

  {"cusparseFillMode_t",                        {"hipsparseFillMode_t",                        "", CONV_TYPE, API_SPARSE}},
  {"CUSPARSE_FILL_MODE_LOWER",                  {"HIPSPARSE_FILL_MODE_LOWER",                  "", CONV_NUMERIC_LITERAL, API_SPARSE}},
  {"CUSPARSE_FILL_MODE_UPPER",                  {"HIPSPARSE_FILL_MODE_UPPER",                  "", CONV_NUMERIC_LITERAL, API_SPARSE}},

  {"cusparseIndexBase_t",                       {"hipsparseIndexBase_t",                       "", CONV_TYPE, API_SPARSE}},
  {"CUSPARSE_INDEX_BASE_ZERO",                  {"HIPSPARSE_INDEX_BASE_ZERO",                  "", CONV_NUMERIC_LITERAL, API_SPARSE}},
  {"CUSPARSE_INDEX_BASE_ONE",                   {"HIPSPARSE_INDEX_BASE_ONE",                   "", CONV_NUMERIC_LITERAL, API_SPARSE}},

  {"cusparseMatrixType_t",                      {"hipsparseMatrixType_t",                      "", CONV_TYPE, API_SPARSE}},
  {"CUSPARSE_MATRIX_TYPE_GENERAL",              {"HIPSPARSE_MATRIX_TYPE_GENERAL",              "", CONV_NUMERIC_LITERAL, API_SPARSE}},
  {"CUSPARSE_MATRIX_TYPE_SYMMETRIC",            {"HIPSPARSE_MATRIX_TYPE_SYMMETRIC",            "", CONV_NUMERIC_LITERAL, API_SPARSE}},
  {"CUSPARSE_MATRIX_TYPE_HERMITIAN",            {"HIPSPARSE_MATRIX_TYPE_HERMITIAN",            "", CONV_NUMERIC_LITERAL, API_SPARSE}},
  {"CUSPARSE_MATRIX_TYPE_TRIANGULAR",           {"HIPSPARSE_MATRIX_TYPE_TRIANGULAR",           "", CONV_NUMERIC_LITERAL, API_SPARSE}},

  {"cusparseOperation_t",                       {"hipsparseOperation_t",                       "", CONV_TYPE, API_SPARSE}},
  {"CUSPARSE_OPERATION_NON_TRANSPOSE",          {"HIPSPARSE_OPERATION_NON_TRANSPOSE",          "", CONV_NUMERIC_LITERAL, API_SPARSE}},
  {"CUSPARSE_OPERATION_TRANSPOSE",              {"HIPSPARSE_OPERATION_TRANSPOSE",              "", CONV_NUMERIC_LITERAL, API_SPARSE}},
  {"CUSPARSE_OPERATION_CONJUGATE_TRANSPOSE",    {"HIPSPARSE_OPERATION_CONJUGATE_TRANSPOSE",    "", CONV_NUMERIC_LITERAL, API_SPARSE}},

  {"cusparsePointerMode_t",                     {"hipsparsePointerMode_t",                     "", CONV_TYPE, API_SPARSE}},
  {"CUSPARSE_POINTER_MODE_HOST",                {"HIPSPARSE_POINTER_MODE_HOST",                "", CONV_NUMERIC_LITERAL, API_SPARSE}},
  {"CUSPARSE_POINTER_MODE_DEVICE",              {"HIPSPARSE_POINTER_MODE_DEVICE",              "", CONV_NUMERIC_LITERAL, API_SPARSE}},

  {"cusparseAlgMode_t",                         {"hipsparseAlgMode_t",                         "", CONV_TYPE, API_SPARSE, HIP_UNSUPPORTED}},
  {"CUSPARSE_ALG0",                             {"CUSPARSE_ALG0",                              "", CONV_NUMERIC_LITERAL, API_SPARSE, HIP_UNSUPPORTED}},
  {"CUSPARSE_ALG1",                             {"CUSPARSE_ALG1",                              "", CONV_NUMERIC_LITERAL, API_SPARSE, HIP_UNSUPPORTED}},
  {"CUSPARSE_ALG_NAIVE",                        {"CUSPARSE_ALG_NAIVE",                         "", CONV_NUMERIC_LITERAL, API_SPARSE, HIP_UNSUPPORTED}},
  {"CUSPARSE_ALG_MERGE_PATH",                   {"CUSPARSE_ALG_MERGE_PATH",                    "", CONV_NUMERIC_LITERAL, API_SPARSE, HIP_UNSUPPORTED}},

  {"cusparseSolvePolicy_t",                     {"hipsparseSolvePolicy_t",                     "", CONV_TYPE, API_SPARSE}},
  {"CUSPARSE_SOLVE_POLICY_NO_LEVEL",            {"HIPSPARSE_SOLVE_POLICY_NO_LEVEL",            "", CONV_NUMERIC_LITERAL, API_SPARSE}},
  {"CUSPARSE_SOLVE_POLICY_USE_LEVEL",           {"HIPSPARSE_SOLVE_POLICY_USE_LEVEL",           "", CONV_NUMERIC_LITERAL, API_SPARSE}},

  {"cusparseStatus_t",                          {"hipsparseStatus_t",                          "", CONV_TYPE, API_SPARSE}},
  {"CUSPARSE_STATUS_SUCCESS",                   {"HIPSPARSE_STATUS_SUCCESS",                   "", CONV_NUMERIC_LITERAL, API_SPARSE}},
  {"CUSPARSE_STATUS_NOT_INITIALIZED",           {"HIPSPARSE_STATUS_NOT_INITIALIZED",           "", CONV_NUMERIC_LITERAL, API_SPARSE}},
  {"CUSPARSE_STATUS_ALLOC_FAILED",              {"HIPSPARSE_STATUS_ALLOC_FAILED",              "", CONV_NUMERIC_LITERAL, API_SPARSE}},
  {"CUSPARSE_STATUS_INVALID_VALUE",             {"HIPSPARSE_STATUS_INVALID_VALUE",             "", CONV_NUMERIC_LITERAL, API_SPARSE}},
  {"CUSPARSE_STATUS_ARCH_MISMATCH",             {"HIPSPARSE_STATUS_ARCH_MISMATCH",             "", CONV_NUMERIC_LITERAL, API_SPARSE}},
  {"CUSPARSE_STATUS_MAPPING_ERROR",             {"HIPSPARSE_STATUS_MAPPING_ERROR",             "", CONV_NUMERIC_LITERAL, API_SPARSE}},
  {"CUSPARSE_STATUS_EXECUTION_FAILED",          {"HIPSPARSE_STATUS_EXECUTION_FAILED",          "", CONV_NUMERIC_LITERAL, API_SPARSE}},
  {"CUSPARSE_STATUS_INTERNAL_ERROR",            {"HIPSPARSE_STATUS_INTERNAL_ERROR",            "", CONV_NUMERIC_LITERAL, API_SPARSE}},
  {"CUSPARSE_STATUS_MATRIX_TYPE_NOT_SUPPORTED", {"HIPSPARSE_STATUS_MATRIX_TYPE_NOT_SUPPORTED", "", CONV_NUMERIC_LITERAL, API_SPARSE}},
  {"CUSPARSE_STATUS_ZERO_PIVOT",                {"HIPSPARSE_STATUS_ZERO_PIVOT",                "", CONV_NUMERIC_LITERAL, API_SPARSE}},

  {"cusparseCsr2CscAlg_t",                      {"hipsparseCsr2CscAlg_t",                      "", CONV_TYPE, API_SPARSE, HIP_UNSUPPORTED}},
  {"CUSPARSE_CSR2CSC_ALG1",                     {"HIPSPARSE_CSR2CSC_ALG1",                     "", CONV_NUMERIC_LITERAL, API_SPARSE, HIP_UNSUPPORTED}},
  {"CUSPARSE_CSR2CSC_ALG2",                     {"HIPSPARSE_CSR2CSC_ALG2",                     "", CONV_NUMERIC_LITERAL, API_SPARSE, HIP_UNSUPPORTED}},

  {"cusparseFormat_t",                          {"hipsparseFormat_t",                          "", CONV_TYPE, API_SPARSE, HIP_UNSUPPORTED}},
  {"CUSPARSE_FORMAT_CSR",                       {"HIPSPARSE_FORMAT_CSR",                       "", CONV_NUMERIC_LITERAL, API_SPARSE, HIP_UNSUPPORTED}},
  {"CUSPARSE_FORMAT_CSC",                       {"HIPSPARSE_FORMAT_CSC",                       "", CONV_NUMERIC_LITERAL, API_SPARSE, HIP_UNSUPPORTED}},
  {"CUSPARSE_FORMAT_COO",                       {"HIPSPARSE_FORMAT_COO",                       "", CONV_NUMERIC_LITERAL, API_SPARSE, HIP_UNSUPPORTED}},
  {"CUSPARSE_FORMAT_COO_AOS",                   {"HIPSPARSE_FORMAT_COO_AOS",                   "", CONV_NUMERIC_LITERAL, API_SPARSE, HIP_UNSUPPORTED}},

  {"cusparseOrder_t",                           {"hipsparseOrder_t",                           "", CONV_TYPE, API_SPARSE, HIP_UNSUPPORTED}},
  {"CUSPARSE_ORDER_COL",                        {"HIPSPARSE_ORDER_COL",                        "", CONV_NUMERIC_LITERAL, API_SPARSE, HIP_UNSUPPORTED}},
  {"CUSPARSE_ORDER_ROW",                        {"HIPSPARSE_ORDER_ROW",                        "", CONV_NUMERIC_LITERAL, API_SPARSE, HIP_UNSUPPORTED}},

  {"cusparseSpMVAlg_t",                         {"hipsparseSpMVAlg_t",                         "", CONV_TYPE, API_SPARSE, HIP_UNSUPPORTED}},
  {"CUSPARSE_MV_ALG_DEFAULT",                   {"HIPSPARSE_MV_ALG_DEFAULT",                   "", CONV_NUMERIC_LITERAL, API_SPARSE, HIP_UNSUPPORTED}},
  {"CUSPARSE_COOMV_ALG",                        {"HIPSPARSE_COOMV_ALG",                        "", CONV_NUMERIC_LITERAL, API_SPARSE, HIP_UNSUPPORTED}},
  {"CUSPARSE_CSRMV_ALG1",                       {"HIPSPARSE_CSRMV_ALG1",                       "", CONV_NUMERIC_LITERAL, API_SPARSE, HIP_UNSUPPORTED}},
  {"CUSPARSE_CSRMV_ALG2",                       {"HIPSPARSE_CSRMV_ALG2",                       "", CONV_NUMERIC_LITERAL, API_SPARSE, HIP_UNSUPPORTED}},

  {"cusparseSpMMAlg_t",                         {"hipsparseSpMMAlg_t",                         "", CONV_TYPE, API_SPARSE, HIP_UNSUPPORTED}},
  {"CUSPARSE_MM_ALG_DEFAULT",                   {"HIPSPARSE_MM_ALG_DEFAULT",                   "", CONV_NUMERIC_LITERAL, API_SPARSE, HIP_UNSUPPORTED}},
  {"CUSPARSE_COOMM_ALG1",                       {"HIPSPARSE_COOMM_ALG1",                       "", CONV_NUMERIC_LITERAL, API_SPARSE, HIP_UNSUPPORTED}},
  {"CUSPARSE_COOMM_ALG2",                       {"HIPSPARSE_COOMM_ALG2",                       "", CONV_NUMERIC_LITERAL, API_SPARSE, HIP_UNSUPPORTED}},
  {"CUSPARSE_COOMM_ALG3",                       {"HIPSPARSE_COOMM_ALG3",                       "", CONV_NUMERIC_LITERAL, API_SPARSE, HIP_UNSUPPORTED}},
  {"CUSPARSE_CSRMM_ALG1",                       {"HIPSPARSE_CSRMM_ALG1",                       "", CONV_NUMERIC_LITERAL, API_SPARSE, HIP_UNSUPPORTED}},

  {"cusparseIndexType_t",                       {"hipsparseIndexType_t",                       "", CONV_TYPE, API_SPARSE, HIP_UNSUPPORTED}},
  {"CUSPARSE_INDEX_16U",                        {"HIPSPARSE_INDEX_16U",                        "", CONV_NUMERIC_LITERAL, API_SPARSE, HIP_UNSUPPORTED}},
  {"CUSPARSE_INDEX_32I",                        {"HIPSPARSE_INDEX_32I",                        "", CONV_NUMERIC_LITERAL, API_SPARSE, HIP_UNSUPPORTED}},
  {"CUSPARSE_INDEX_64I",                        {"HIPSPARSE_INDEX_64I",                        "", CONV_NUMERIC_LITERAL, API_SPARSE, HIP_UNSUPPORTED}},

  // 3. Defines
  {"CUSPARSE_VER_MAJOR",                        {"HIPSPARSE_VER_MAJOR",                        "", CONV_DEFINE, API_SPARSE, HIP_UNSUPPORTED}},
  {"CUSPARSE_VER_MINOR",                        {"HIPSPARSE_VER_MINOR",                        "", CONV_DEFINE, API_SPARSE, HIP_UNSUPPORTED}},
  {"CUSPARSE_VER_PATCH",                        {"HIPSPARSE_VER_PATCH",                        "", CONV_DEFINE, API_SPARSE, HIP_UNSUPPORTED}},
  {"CUSPARSE_VER_BUILD",                        {"HIPSPARSE_VER_BUILD",                        "", CONV_DEFINE, API_SPARSE, HIP_UNSUPPORTED}},
  {"CUSPARSE_VERSION",                          {"HIPSPARSE_VERSION",                          "", CONV_DEFINE, API_SPARSE, HIP_UNSUPPORTED}},
};
