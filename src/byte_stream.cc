#include "byte_stream.hh"


using namespace std;

ByteStream::ByteStream( uint64_t capacity )
  : capacity_( capacity )
  , close_( false )
  , error_( false )
  , begin_(0)
  , end_(0)
  , content_("")
  , pushed_cnt_( 0 )
  , poped_cnt_( 0 )
{}
void ByteStream::print_status()
{
  fprintf( stdout,
           "poped: %ld\tpushed: %ld\tcapacity: %ld\n",
           poped_cnt_,
           pushed_cnt_,
           capacity_ );
}

bool Writer::is_closed() const
{
  // Your code here.
  return close_;
}

void Writer::push( string data )
{
  if (is_closed()) return;
  if (end_ + data.size() > capacity_) {
    content_.replace(0, end_ - begin_, content_, begin_, end_ - begin_);
    end_ = end_ - begin_;
    begin_ = 0;
  }
  if (end_ + data.size() <= capacity_) {
    content_.replace(end_, data.size(), data);
    pushed_cnt_ += data.size();
    end_ += data.size();
  } else {
    content_.replace(end_, capacity_ - end_, data, 0, capacity_ - end_);
    pushed_cnt_ += (capacity_ - end_);
    end_ = capacity_;
  }
}

void Writer::close()
{
  // Your code here.
  close_ = true;
}

uint64_t Writer::available_capacity() const
{
  return ( capacity_ - (end_ - begin_) );
}

uint64_t Writer::bytes_pushed() const
{
  // Your code here.
  return pushed_cnt_;
}

bool Reader::is_finished() const
{
  // Your code here.
  return ( close_ && ( begin_ == end_ ) );
}

uint64_t Reader::bytes_popped() const
{
  // Your code here.
  return poped_cnt_;
}

string_view Reader::peek() const
{
  return string_view(content_.data() + begin_, end_ - begin_);
}

void Reader::pop( uint64_t len )
{
  // Your code here.
  if (begin_ + len <= end_) {
    begin_ += len;
    poped_cnt_ += len;
  } else {
    std::cerr << "pop len greater than size" << std::endl;
    begin_ = end_;
    poped_cnt_ += (end_ - begin_);
  }
  // print_status();
}

uint64_t Reader::bytes_buffered() const
{
  return end_ - begin_;
}
