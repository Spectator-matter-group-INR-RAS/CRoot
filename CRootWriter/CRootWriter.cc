/**
 * CRoot - COLA Library Module for ROOT data storage support.
 * Copyright (C) 2025-2026 Savva Savenkov
 *
 * This file is part of CRoot
 *
 * CRoot is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * CRoot is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with CRoot.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "CRootWriter.hh"

using namespace cola;

CRootWriter::CRootWriter(const std::string& f_name, size_t buff_size)
    : output_file_(std::unique_ptr<TFile>(TFile::Open(f_name.c_str(), "RECREATE"))), buff_size_(buff_size), count_(0) {}

CRootWriter::~CRootWriter() {
  for (auto&& tree : output_tree_map_) {
    tree.second->Write();
  }
  output_file_->Save();
  output_file_->Close();
}

void CRootWriter::operator()(std::unique_ptr<EventData>&& data) {
  WriteEvent(std::move(data));
  count_++;
  /*if (count_ % buff_size_ == 0)
      for (auto&& tree : output_tree_map_)
          tree.second->Write();*/
}
