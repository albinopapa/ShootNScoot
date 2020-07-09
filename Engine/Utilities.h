#pragma once
//why?
template<typename Container, typename Pred>
void erase_if( Container* container_, Pred pred_ )noexcept
{
	auto last_elem = 
		std::remove_if( container_.begin(), container_.end(), pred_ );

	container_.erase( last_elem, container_.end() );
}
