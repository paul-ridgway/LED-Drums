require 'rubyserial'
require 'pp'

class SerialCommand

	def initialize(tty, baud)
		@tty = tty
		@baud = baud
	end

	def connect!
		puts "Connecting..."
		@comm = Serial.new @tty, @baud
		puts "Connected!"
	end

	def wait_for(command, limit = 9999999)
		# puts "Wait for: #{command}"
		match = false
		attempts = 0
		while(!match && attempts < limit)
			str = @comm.read(1)
			d = str.each_byte.map do |i|
				if i == command
					match = true
					break
				end
			end
			sleep 0.001 unless match
			attempts += 1
			if (attempts % 1000 == 0) 
				puts "Stalled waiting for #{command}"
			end
		end
	end


	def write(command, data = [])
		data.map!{ |i| i == 255 ? 254 : i}
		data = [255, command] + data
		@comm.write(data.pack('c*'))	
	end

	def clear
		write(CLEAR)
		wait_for(CLEAR)
	end

end