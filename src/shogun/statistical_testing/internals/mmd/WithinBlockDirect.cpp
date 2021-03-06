/*
 * Restructuring Shogun's statistical hypothesis testing framework.
 * Copyright (C) 2014  Soumyajit De
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http:/www.gnu.org/licenses/>.
 */

#include <shogun/lib/SGMatrix.h>
#include <shogun/lib/GPUMatrix.h>
#include <shogun/mathematics/eigen3.h>
#include <shogun/mathematics/Math.h>
#include <shogun/statistical_testing/internals/mmd/WithinBlockDirect.h>

using namespace shogun;
using namespace internal;
using namespace mmd;

float32_t WithinBlockDirect::operator()(const SGMatrix<float32_t>& km)
{
	Eigen::Map<Eigen::MatrixXf> map(km.matrix, km.num_rows, km.num_cols);
	index_t B=km.num_rows;

	Eigen::VectorXf diag=map.diagonal();
	map.diagonal().setZero();

	auto term_1=map.array().square().sum();
	auto term_2=CMath::sq(map.array().sum());
	auto term_3=(map*map).array().sum();

	map.diagonal()=diag;

	auto variance_estimate=2*(term_1+term_2/(B-1)/(B-2)-2*term_3/(B-2))/B/(B-3);
	return variance_estimate;
}
