//
// Copyright 2023 Pixar
//
// Licensed under the Apache License, Version 2.0 (the "Apache License")
// with the following modification; you may not use this file except in
// compliance with the Apache License and the following modification to it:
// Section 6. Trademarks. is deleted and replaced with:
//
// 6. Trademarks. This License does not grant permission to use the trade
//    names, trademarks, service marks, or product names of the Licensor
//    and its affiliates, except as required to comply with Section 4(c) of
//    the License and to reproduce the content of the NOTICE file.
//
// You may obtain a copy of the Apache License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the Apache License with the above modification is
// distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied. See the Apache License for the specific
// language governing permissions and limitations under the Apache License.
//
#ifndef PXR_USD_USD_UTILS_USDZ_PACKAGE_H
#define PXR_USD_USD_UTILS_USDZ_PACKAGE_H

/// \file usdUtils/usdzPackage.h

#include "pxr/pxr.h"
#include "pxr/usd/sdf/layer.h"
#include "pxr/usd/usdUtils/api.h"

#include <string>
#include <vector>

PXR_NAMESPACE_OPEN_SCOPE

class SdfAssetPath;

/// Creates a USDZ package containing the specified asset, identified by its 
/// \p assetPath. The created package will include a localized version of the 
/// asset itself and all of its external dependencies. Any anonymous layers that
/// are encountered during dependency discovery will be serialized into the
/// resulting package. Due to localization, the packaged layers might be 
/// modified to have different asset paths.
///
/// You can optionally specify a different package-internal name for the first
/// layer of the asset by specifying \p firstLayerName. By default,
/// \p firstLayerName is empty, meaning that the original name is preserved.
/// 
/// Returns true if the package was created successfully.
/// 
/// \note Clients of this function must take care of configuring the asset 
/// resolver context before invoking the function. To create a default 
/// resolver context, use \ref CreateDefaultContextForAsset() with the 
/// asset path.
/// 
/// \note If the given asset has a dependency on a directory (i.e. an external 
/// reference to a directory path), the dependency is ignored and the contents 
/// of the directory are not included in the created package. 
/// 
/// \note This function modifies the layers referenced by \p assetPath 
/// (including the root layer and all transitive layer dependencies) in-place. 
/// However, it does not save the layers before copying them into the package 
/// that is created. It also does not revert the changes it makes to the 
/// layers. Therefore, it is strongly recommended that you run this function in 
/// isolation after any source UsdStages have been closed. If you have UsdStages 
/// open during the function call that reference the layers being modified, you 
/// may receive warnings or composition errors which may not affect the 
/// resulting package adversely.
/// 
/// \sa UsdUtilsCreateNewARKitUsdzPackage()
USDUTILS_API
bool
UsdUtilsCreateNewUsdzPackage(
    const SdfAssetPath& assetPath,
    const std::string& usdzFilePath,
    const std::string& firstLayerName=std::string());

/// Similar to UsdUtilsCreateNewUsdzPackage, this function packages all of the 
/// dependencies of the given asset. Assets targeted at the initial usdz 
/// implementation in ARKit operate under greater constraints than usdz files 
/// for more general 'in house' uses, and this option attempts to ensure that
/// these constraints are honored; this may involve more transformations to the 
/// data, which may cause loss of features such as VariantSets. Any anonymous 
/// layers that are encountered during dependency discovery will be serialized 
/// into the resulting package.
///
/// If \p firstLayerName is specified, it is modified to have the ".usdc" 
/// extension, as required by the initial usdz implementation in ARKit.
/// 
/// Returns true if the package was created successfully.
/// 
/// \note Clients of this function must take care of configuring the asset 
/// resolver context before invoking the function. To create a default 
/// resolver context, use \ref CreateDefaultContextForAsset() with the 
/// asset path.
/// 
/// \note If the given asset has a dependency on a directory (i.e. an external 
/// reference to a directory path), the dependency is ignored and the contents 
/// of the directory are not included in the created package. 
/// 
/// \note This function modifies the layers referenced by \p assetPath 
/// (including the root layer and all transitive layer dependencies) in-place. 
/// However, it does not save the layers before copying them into the package 
/// that is created. It also does not revert the changes it makes to the 
/// layers. Therefore, it is strongly recommended that you run this function in 
/// isolation after any source UsdStages have been closed. If you have UsdStages 
/// open during the function call that reference the layers being modified, you 
/// may receive warnings or composition errors which may not affect the 
/// resulting package adversely.  
/// 
/// \sa UsdUtilsCreateNewUsdzPackage()
USDUTILS_API
bool
UsdUtilsCreateNewARKitUsdzPackage(
    const SdfAssetPath &assetPath,
    const std::string &usdzFilePath,
    const std::string &firstLayerName=std::string());

PXR_NAMESPACE_CLOSE_SCOPE

#endif // PXR_USD_USD_UTILS_USDZ_PACKAGE_H
